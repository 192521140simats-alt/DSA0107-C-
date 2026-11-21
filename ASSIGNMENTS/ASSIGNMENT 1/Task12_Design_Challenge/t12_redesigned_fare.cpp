#include <iostream>
#include <iomanip>
#include <array>
#include <string>

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };

struct MonthlyPass {
    bool active;
    Zone zoneA;
    Zone zoneB;

    bool covers(Zone z) const {
        return active && (z == zoneA || z == zoneB);
    }
};

class RevisedFareEngine {
private:
    static constexpr std::array<long long, 4> ZONE_BASE_PAISE = {1000, 2000, 3000, 6000};
    static constexpr int PEAK_SURCHARGE_PCT = 20;
    static constexpr int WEEKEND_DISCOUNT_PCT = 10;

public:
    static bool isPeakHour(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    // Rule: Weekend discount (10%) does NOT combine with peak surcharge
    static long long computeFarePaise(Zone z, int hour, bool isWeekend, const MonthlyPass& pass) {
        if (pass.covers(z)) {
            return 0LL; // Covered by monthly pass for two chosen zones
        }
        long long base = ZONE_BASE_PAISE[static_cast<std::size_t>(z)];
        if (isWeekend) {
            return (base * (100 - WEEKEND_DISCOUNT_PCT)) / 100;
        }
        if (isPeakHour(hour)) {
            return base + (base * PEAK_SURCHARGE_PCT) / 100;
        }
        return base;
    }
};

int main() {
    MonthlyPass pass{true, Zone::Inner, Zone::Middle};
    MonthlyPass noPass{false, Zone::Inner, Zone::Inner};

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "1) Airport weekday peak (09h, no pass): Rs "
              << (RevisedFareEngine::computeFarePaise(Zone::Airport, 9, false, noPass) / 100.0) << "\n";
    std::cout << "2) Airport weekend peak-hour window (09h, weekend, no pass): Rs "
              << (RevisedFareEngine::computeFarePaise(Zone::Airport, 9, true, noPass) / 100.0) << "\n";
    std::cout << "3) Middle covered by pass (09h, weekday): Rs "
              << (RevisedFareEngine::computeFarePaise(Zone::Middle, 9, false, pass) / 100.0) << "\n";
    std::cout << "4) Airport NOT covered by pass (14h, weekday): Rs "
              << (RevisedFareEngine::computeFarePaise(Zone::Airport, 14, false, pass) / 100.0) << "\n";
    return 0;
}
