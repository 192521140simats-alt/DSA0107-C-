#include <iostream>
#include <iomanip>
#include <array>

enum class Zone { Inner = 0, Middle = 1, Outer = 2, COUNT = 3 };

struct GatePolicy {
    static constexpr std::array<long long, 3> BASE_FARE_PAISE = {1000, 2000, 3000};
    static constexpr int PEAK_SURCHARGE_PCT = 20;
    static constexpr long long MIN_KEEP_PAISE = 5000;

    static constexpr bool isPeak(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static constexpr long long farePaise(Zone z, int hour) {
        long long base = BASE_FARE_PAISE[static_cast<std::size_t>(z)];
        return isPeak(hour) ? (base + (base * PEAK_SURCHARGE_PCT) / 100) : base;
    }
};

int main() {
    constexpr long long sample = GatePolicy::farePaise(Zone::Outer, 9);
    std::cout << "Recommended GatePolicy constexpr Outer@09:00 = " << sample
              << " paise (Rs " << std::fixed << std::setprecision(2) << (sample / 100.0) << ")\n";
    return 0;
}
