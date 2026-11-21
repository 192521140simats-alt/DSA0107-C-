#include <iostream>
#include <iomanip>
#include <climits>

void runScale(long long n, long long farePaise) {
    long long paiseTotal = n * farePaise;
    double fareRupees = static_cast<double>(farePaise) / 100.0;
    double dblTotal = 0.0;
    for (long long i = 0; i < n; ++i) {
        dblTotal += fareRupees;
    }
    double exactRupees = static_cast<double>(paiseTotal) / 100.0;
    double diffRupees = dblTotal - exactRupees;

    std::cout << "Scale N=" << std::setw(8) << n
              << " | PaiseSum=" << std::setw(13) << paiseTotal
              << " | ExactRs=" << std::setw(12) << std::fixed << std::setprecision(2) << exactRupees
              << " | DblSumRs=" << std::setw(12) << dblTotal
              << " | DiffRs=" << std::setprecision(6) << diffRupees << "\n";
}

int main() {
    std::cout << "INT_MAX = " << INT_MAX << " (~2.147e9)\n";
    runScale(20000LL,   2400LL); // 48,000,000 paise -> fits int
    runScale(500000LL,  2400LL); // 1,200,000,000 paise -> fits int
    runScale(3000000LL, 2400LL); // 7,200,000,000 paise -> OVERFLOWS 32-bit int!

    long long netPaise = 3000000LL * 2400LL;
    int badInt = static_cast<int>(netPaise);
    std::cout << "3,000,000 * 2400 paise in long long: " << netPaise
              << " | in 32-bit int: " << badInt << "\n";
    return 0;
}
