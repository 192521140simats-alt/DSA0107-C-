#include <iomanip>
#include <iostream>

enum class Zone { Inner, Middle, Outer };

constexpr int BASE_PAISE[] = {1000, 2000, 3000};   // Rs 10, Rs 20, Rs 30
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;    // Rs 50 must remain on the card

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

long long fare(Zone z, bool peak)
{
    // TODO 1: Use a switch on z to pick the base fare from BASE_PAISE, then add
    //   PEAK_SURCHARGE_PERCENT % in peak hours using integer arithmetic only
    long long base = 0;
    switch (z) {
        case Zone::Inner:  base = BASE_PAISE[0]; break;
        case Zone::Middle: base = BASE_PAISE[1]; break;
        case Zone::Outer:  base = BASE_PAISE[2]; break;
        default:           return -1;
    }
    if (peak) {
        base = base + (base * PEAK_SURCHARGE_PERCENT) / 100;
    }
    return base;
}

bool canTravel(long long balance, long long f)
{
    // TODO 2: Return true only if the balance left after paying the fare is at least
    //   MIN_BALANCE_PAISE
    if (f < 0) return false;
    return (balance - f) >= MIN_BALANCE_PAISE;
}

int main()
{
    long long balance = 10000;                       // Rs 100.00 in paise
    struct Trip { Zone zone; int hour; };
    Trip trips[] = {
        {Zone::Inner,  9},   // Rs 10.00 off-peak trip test vs expected sequence
        {Zone::Outer,  9},   // Rs 36.00 peak
        {Zone::Middle, 14},  // Denied: 6400 - 2000 = 4400 < 5000
        {Zone::Inner,  10},  // Exactly 10 AM -> off-peak (Rs 10.00)
        {Zone::Outer,  20}   // Exactly 8 PM -> off-peak (Rs 30.00)
    };

    // Exact expected snippet first:
    long long demoBal = 10000;
    struct DemoTrip { Zone zone; bool peak; };
    DemoTrip demo[] = {{Zone::Inner, false}, {Zone::Outer, true}, {Zone::Middle, false}};
    for (const DemoTrip& t : demo) {
        long long f = fare(t.zone, t.peak);
        if (canTravel(demoBal, f)) {
            demoBal -= f;
            std::cout << "Fare Rs " << f / 100 << '.' << std::setw(2)
                      << std::setfill('0') << f % 100 << std::setfill(' ');
        } else {
            std::cout << "Denied (low balance)";
        }
        std::cout << "  balance Rs " << demoBal / 100 << '\n';
    }

    std::cout << "--- Boundary Check (10 AM & 8 PM) ---\n";
    for (const Trip& tr : trips) {
        bool pk = isPeakHour(tr.hour);
        long long f = fare(tr.zone, pk);
        std::cout << "Hour " << std::setw(2) << tr.hour << " (peak=" << pk << ") -> Fare Rs "
                  << (f / 100) << "." << std::setw(2) << std::setfill('0') << (f % 100)
                  << std::setfill(' ') << "\n";
    }
    return 0;
}
