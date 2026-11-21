#include <iostream>

constexpr bool isPeakHourExpr(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

int main() {
    constexpr bool peakTable[24] = {
        false, false, false, false, false, false, false, false, // 0..7
        true,  true,                                             // 8..9 (10 is off-peak)
        false, false, false, false, false, false, false,         // 10..16
        true,  true,  true,                                      // 17..19 (20 is off-peak)
        false, false, false, false                               // 20..23
    };

    int testHours[] = {7, 8, 9, 10, 16, 17, 19, 20, 22};
    for (int h : testHours) {
        bool exprRes = (h >= 0 && h < 24) && isPeakHourExpr(h);
        bool tblRes  = (h >= 0 && h < 24) && peakTable[h];
        std::cout << "Hour " << h << ": expr=" << exprRes << ", table=" << tblRes << "\n";
    }
    return 0;
}
