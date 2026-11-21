#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };
enum class Rider { Normal, Student, Senior };

struct TestCase {
    std::string name;
    Zone zone;
    int hour;
    Rider rider;
    long long startBalPaise;
    long long rechargePaise;
    long long expectedFarePaise;
    bool expectedAllowed;
};

long long computeFare(Zone z, int hour, Rider r, bool& valid) {
    valid = true;
    long long base = 0;
    switch (z) {
        case Zone::Inner:  base = 1000; break;
        case Zone::Middle: base = 2000; break;
        case Zone::Outer:  base = 3000; break;
        default: valid = false; return 0;
    }
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    if (peak) base += (base * 20) / 100;
    if (r == Rider::Student || r == Rider::Senior) base = (base * 50) / 100;
    return base;
}

int main() {
    std::vector<TestCase> suite = {
        {"Inner Off-Peak (11h)",  Zone::Inner,  11, Rider::Normal,  10000, 0,    1000, true},
        {"Boundary 08:00 Peak",   Zone::Middle,  8, Rider::Normal,  10000, 0,    2400, true},
        {"Boundary 10:00 OffPk",  Zone::Middle, 10, Rider::Normal,  10000, 0,    2000, true},
        {"Boundary 17:00 Peak",   Zone::Outer,  17, Rider::Normal,  10000, 0,    3600, true},
        {"Boundary 20:00 OffPk",  Zone::Outer,  20, Rider::Normal,  10000, 0,    3000, true},
        {"Exact Rs 50 Left",      Zone::Middle, 12, Rider::Normal,   7000, 0,    2000, true},
        {"Neg Recharge Rejected", Zone::Inner,  12, Rider::Normal,   6000, -500, 1000, true}
    };

    // Hand-calculated 5-journey total:
    // 1) Inner off-peak = 1000p; 2) Middle peak(9h) = 2400p; 3) Outer off-peak(14h) = 3000p;
    // 4) Inner student peak(18h) = (1200/2) = 600p; 5) Outer senior off-peak(21h) = (3000/2) = 1500p
    // Hand sum = 1000 + 2400 + 3000 + 600 + 1500 = 8500 paise (Rs 85.00)
    long long handSumPaise = 1000 + 2400 + 3000 + 600 + 1500;
    std::cout << "Hand-calculated 5-journey total: " << handSumPaise << " paise (Rs 85.00)\n\n";

    int passed = 0;
    for (const auto& tc : suite) {
        long long bal = tc.startBalPaise + (tc.rechargePaise > 0 ? tc.rechargePaise : 0);
        bool valid = false;
        long long f = computeFare(tc.zone, tc.hour, tc.rider, valid);
        bool allowed = valid && ((bal - f) >= 5000);
        if (allowed) bal -= f;
        bool ok = (f == tc.expectedFarePaise) && (allowed == tc.expectedAllowed);
        if (ok) ++passed;
        std::cout << std::left << std::setw(24) << tc.name
                  << " | Fare=" << std::setw(4) << f << " (exp " << tc.expectedFarePaise << ")"
                  << " | Allow=" << allowed << " (exp " << tc.expectedAllowed << ")"
                  << " | " << (ok ? "PASS" : "FAIL") << "\n";
    }
    std::cout << "\nPassed " << passed << " / " << suite.size() << " test cases.\n";
    return 0;
}
