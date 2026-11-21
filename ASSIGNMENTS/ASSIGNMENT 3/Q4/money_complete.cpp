#include <iomanip>
#include <iostream>

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& rhs) const {
        Money res;
        res.paise = paise + rhs.paise;
        return res;
    }

    bool operator==(const Money& rhs) const {
        return paise == rhs.paise;
    }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long total = m.paise;
        if (total < 0) { os << '-'; total = -total; }
        long long r = total / 100;
        long long p = total % 100;
        os << "Rs " << r << '.' << std::setw(2) << std::setfill('0') << p;
        return os;
    }
};

int main()
{
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';
    Money carryTest = Money(0, 75) + Money(0, 50);
    std::cout << "Carry Test (Rs 0.75 + Rs 0.50): " << carryTest << '\n';
}
