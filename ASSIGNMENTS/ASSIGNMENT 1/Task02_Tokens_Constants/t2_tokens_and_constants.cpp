#include <iostream>

#define MACRO_PEAK_SURCHARGE_PCT 20

enum class MetroZone { Inner, Middle, Outer };

namespace MetroConfig {
    constexpr long long INNER_FARE_PAISE  = 1000;
    constexpr long long MIDDLE_FARE_PAISE = 2000;
    constexpr long long OUTER_FARE_PAISE  = 3000;
    constexpr int PEAK_SURCHARGE_PCT      = 20;
    constexpr long long MIN_BALANCE_PAISE = 5000;
    const int MAX_ZONES_SUPPORTED         = 3;

    constexpr long long baseFareFor(MetroZone z) {
        switch (z) {
            case MetroZone::Inner:  return INNER_FARE_PAISE;
            case MetroZone::Middle: return MIDDLE_FARE_PAISE;
            case MetroZone::Outer:  return OUTER_FARE_PAISE;
        }
        return 0;
    }
}

int main() {
    constexpr long long sampleFare = MetroConfig::baseFareFor(MetroZone::Middle) +
        (MetroConfig::baseFareFor(MetroZone::Middle) * MetroConfig::PEAK_SURCHARGE_PCT) / 100;
    std::cout << "Middle peak fare (constexpr): " << sampleFare << " paise\n";
    std::cout << "Macro surcharge value: " << MACRO_PEAK_SURCHARGE_PCT << "% | const max zones: "
              << MetroConfig::MAX_ZONES_SUPPORTED << "\n";
    return 0;
}
