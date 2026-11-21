#include <iostream>
#include <iomanip>
#include <string>

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };
enum class ConcessionType { None = 0, Student = 1, Senior = 2 };

class FareTable {
public:
    static constexpr long long BASE_PAISE[3] = {1000, 2000, 3000};
    static constexpr int PEAK_SURCHARGE_PCT = 20;
    static constexpr int CONCESSION_PCT = 50;

    static bool isPeakHour(int hour) {
        // Peak windows: [8, 10) and [17, 20)
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long computeFarePaise(Zone z, int hour, ConcessionType c) {
        int idx = static_cast<int>(z) - 1;
        long long fare = BASE_PAISE[idx];
        if (isPeakHour(hour)) {
            fare = fare + (fare * PEAK_SURCHARGE_PCT) / 100;
        }
        if (c == ConcessionType::Student || c == ConcessionType::Senior) {
            fare = (fare * (100 - CONCESSION_PCT)) / 100;
        }
        return fare;
    }
};

class SmartCard {
private:
    long long balancePaise;
public:
    static constexpr long long MIN_REMAINING_PAISE = 5000; // Rs 50.00
    explicit SmartCard(long long initialPaise) : balancePaise(initialPaise) {}

    long long getBalancePaise() const { return balancePaise; }
    bool canTravel(long long farePaise) const {
        return farePaise >= 0 && (balancePaise - farePaise) >= MIN_REMAINING_PAISE;
    }
    bool deductFare(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }
};

int main() {
    SmartCard card(12000); // Rs 120.00
    long long f1 = FareTable::computeFarePaise(Zone::Outer, 9, ConcessionType::None); // 3000 * 1.2 = 3600
    bool ok1 = card.deductFare(f1);
    std::cout << "Journey 1 (Outer, 09:00 Peak): " << (ok1 ? "Allowed" : "Denied")
              << " | Fare: Rs." << std::fixed << std::setprecision(2) << (f1 / 100.0)
              << " | Balance: Rs." << (card.getBalancePaise() / 100.0) << "\n";

    long long f2 = FareTable::computeFarePaise(Zone::Outer, 18, ConcessionType::None); // 3600 -> 8400 - 3600 = 4800 < 5000
    bool ok2 = card.deductFare(f2);
    std::cout << "Journey 2 (Outer, 18:00 Peak): " << (ok2 ? "Allowed" : "Denied")
              << " | Attempted Fare: Rs." << (f2 / 100.0)
              << " | Balance: Rs." << (card.getBalancePaise() / 100.0) << "\n";
    return 0;
}
