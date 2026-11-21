#include <iostream>
#include <iomanip>
#include <climits>

int main() {
    std::cout << "sizeof(bool)=" << sizeof(bool)
              << ", sizeof(char)=" << sizeof(char)
              << ", sizeof(int)=" << sizeof(int)
              << ", sizeof(long long)=" << sizeof(long long)
              << ", sizeof(unsigned)=" << sizeof(unsigned)
              << ", sizeof(float)=" << sizeof(float)
              << ", sizeof(double)=" << sizeof(double) << "\n";
    std::cout << "INT_MAX=" << INT_MAX << ", LLONG_MAX=" << LLONG_MAX << "\n";

    // Network collection: 3,000,000 journeys/day * 3600 paise (Rs 36.00) = 10,800,000,000 paise (~1.08e10)
    // Exceeds INT_MAX (2,147,483,647) by ~5x! Fits comfortably in long long.
    long long journeys = 3000000LL;
    long long farePaise = 3600LL;
    long long totalPaise = journeys * farePaise;
    int overflowInt = static_cast<int>(totalPaise);

    std::cout << "3,000,000 journeys * 3600 paise (long long): " << totalPaise << "\n";
    std::cout << "Truncated into 32-bit int (overflow!)     : " << overflowInt << "\n";

    // Precision drift measurement adding 10.10 rupees (or 10.33 rupees) n times in double vs paise
    const int N = 3000000;
    double dblSum = 0.0;
    long long paiseSum = 0LL;
    for (int i = 0; i < N; ++i) {
        dblSum += 10.33;
        paiseSum += 1033LL;
    }
    double exactRs = static_cast<double>(paiseSum) / 100.0;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Sum of 3,000,000 * 10.33 (double): " << dblSum << "\n";
    std::cout << "Sum of 3,000,000 * 1033p / 100   : " << exactRs << "\n";
    std::cout << "Absolute rounding drift (double - exact): " << (dblSum - exactRs) << " Rs\n";
    return 0;
}
