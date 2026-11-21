#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>

class Money {
    long long paise;
    explicit Money(long long rawPaise, bool) : paise(rawPaise) {}
public:
    Money(long long rupees = 0, int p = 0) {
        long long sign = (rupees < 0 || p < 0) ? -1 : 1;
        paise = sign * (std::llabs(rupees) * 100 + std::abs(p));
    }
    Money operator+(const Money& rhs) const { return Money(paise + rhs.paise, true); }
    Money operator-(const Money& rhs) const {
        long long diff = paise - rhs.paise;
        if (diff < 0) throw std::underflow_error("Billing Error: Resulting Money amount cannot be negative.");
        return Money(diff, true);
    }
    Money& operator+=(const Money& rhs) { paise += rhs.paise; return *this; }
    Money operator*(int qty) const { return Money(paise * qty, true); }
    friend Money operator*(int qty, const Money& m) { return Money(m.paise * qty, true); }
    bool operator==(const Money& rhs) const { return paise == rhs.paise; }
    bool operator<(const Money& rhs) const  { return paise < rhs.paise; }
    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long r = m.paise / 100;
        long long p = m.paise % 100;
        os << "Rs " << r << '.' << std::setw(2) << std::setfill('0') << p;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Money& m) {
        long long r = 0; int p = 0; char dot = '.';
        if (is >> r >> dot >> p) {
            if (r < 0 || p < 0 || p >= 100 || dot != '.') is.setstate(std::ios::failbit);
            else m = Money(r, p);
        }
        return is;
    }
};

int main() {
    std::cout << "=== Q4: Billing Counter Money Arithmetic ===\n\n";
    Money item1(149, 50), item2(85, 75), discount(20, 0);
    Money bill = (item1 * 2) + item2 - discount;
    bill += Money(12, 25);
    std::cout << "Item 1 (x2): " << (item1 * 2) << '\n';
    std::cout << "Item 2     : " << item2 << '\n';
    std::cout << "Discount   : -" << discount << '\n';
    std::cout << "Pkg Fee    : +Rs 12.25\n";
    std::cout << "Final Bill : " << bill << '\n';

    Money p1(0, 75), p2(0, 50);
    std::cout << "\nPaise Carry Test: " << p1 << " + " << p2 << " = " << (p1 + p2) << '\n';

    std::istringstream iss("345.80");
    Money parsed;
    iss >> parsed;
    std::cout << "Parsed from input stream (\"345.80\"): " << parsed << '\n';

    std::cout << "\n--- Negative Subtraction Guard Test ---\n";
    try {
        Money bad = Money(50, 0) - Money(75, 0);
        std::cout << bad << '\n';
    } catch (const std::underflow_error& e) {
        std::cout << "Caught Exception: " << e.what() << '\n';
    }

    std::cout << "\n--- Precision Experiment: 1,000,000 Additions of Rs 0.10 ---\n";
    Money exactSum(0, 0);
    double doubleSum = 0.0;
    for (int i = 0; i < 1000000; ++i) {
        exactSum += Money(0, 10);
        doubleSum += 0.10;
    }
    std::cout << "Expected Exact Total  : Rs 100000.00\n";
    std::cout << "Money (long long) Sum : " << exactSum << " (0 error)\n";
    std::cout << "double Sum            : Rs " << std::fixed << std::setprecision(10) << doubleSum
              << " (drift = " << std::abs(doubleSum - 100000.0) << ")\n";
    return 0;
}
