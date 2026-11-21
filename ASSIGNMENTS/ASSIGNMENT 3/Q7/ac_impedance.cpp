#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

class Complex {
    double re;
    double im;

public:
    Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}

    double real() const { return re; }
    double imag() const { return im; }
    double magnitude() const { return std::hypot(re, im); }

    bool operator==(const Complex& rhs) const {
        return std::fabs(re - rhs.re) < 1e-9 && std::fabs(im - rhs.im) < 1e-9;
    }

    friend Complex operator+(const Complex& a, const Complex& b) {
        return Complex(a.re + b.re, a.im + b.im);
    }

    friend Complex operator-(const Complex& a, const Complex& b) {
        return Complex(a.re - b.re, a.im - b.im);
    }

    friend Complex operator*(const Complex& a, const Complex& b) {
        return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
    }

    friend Complex operator/(const Complex& a, const Complex& b) {
        double denom = b.re * b.re + b.im * b.im;
        if (denom < 1e-12) {
            throw std::domain_error("Impedance Error: Division by zero impedance (short circuit).");
        }
        return Complex((a.re * b.re + a.im * b.im) / denom,
                       (a.im * b.re - a.re * b.im) / denom);
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& z) {
        os << std::fixed << std::setprecision(4) << z.re
           << (z.im >= 0 ? " + " : " - ") << std::fabs(z.im) << 'j';
        return os;
    }
};

int main() {
    std::cout << "=== Q7: AC Circuit Impedance Calculator ===\n\n";
    double omega = 100.0, R = 10.0, L = 0.2, C = 0.001;
    Complex Z_R(R);
    Complex Z_L(0.0, omega * L);
    Complex Z_C(0.0, -1.0 / (omega * C));

    std::cout << "Component Impedances at omega = " << omega << " rad/s:\n";
    std::cout << "  Z_R = " << Z_R << " ohm\n";
    std::cout << "  Z_L = " << Z_L << " ohm\n";
    std::cout << "  Z_C = " << Z_C << " ohm\n\n";

    Complex Z_series = Z_R + Z_L + Z_C;
    std::cout << "Series RLC Impedance   : " << Z_series
              << " ohm | Magnitude |Z| = " << Z_series.magnitude() << " ohm\n";

    Complex Z_branch1 = Z_R + Z_L;
    Complex Z_parallel = (Z_branch1 * Z_C) / (Z_branch1 + Z_C);
    std::cout << "Parallel RLC Impedance : " << Z_parallel
              << " ohm | Magnitude |Z| = " << Z_parallel.magnitude() << " ohm\n\n";

    Complex expectedSeries(10.0, 10.0), expectedParallel(5.0, -15.0);
    std::cout << "Matches hand-calculated series (10 + 10j)   : " << std::boolalpha << (Z_series == expectedSeries) << '\n';
    std::cout << "Matches hand-calculated parallel (5 - 15j)  : " << (Z_parallel == expectedParallel) << "\n\n";

    std::cout << "--- Division by Zero Impedance Test ---\n";
    try {
        Complex Z_zero;
        Complex Z_fault = Z_R / Z_zero;
        std::cout << Z_fault << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Caught Exception: " << e.what() << '\n';
    }
    return 0;
}
