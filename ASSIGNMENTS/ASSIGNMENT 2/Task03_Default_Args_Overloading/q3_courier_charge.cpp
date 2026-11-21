#include <iostream>
#include <iomanip>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(double weightKg, bool express = false, bool insured = false) {
    double base = 40.0 + weightKg * 15.0;
    if (express) base += 60.0;
    if (insured) base += 35.0;
    return base;
}

double charge(int weightGrams, bool express = false, bool insured = false) {
    return charge(static_cast<double>(weightGrams) / 1000.0, express, insured);
}

double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    Parcel p1{3.0, true, false};
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "1. charge(2.0)              = " << charge(2.0) << "\n";
    std::cout << "2. charge(2.0, true)        = " << charge(2.0, true) << "\n";
    std::cout << "3. charge(2.0, true, true)  = " << charge(2.0, true, true) << "\n";
    std::cout << "4. charge(2) [int grams]    = " << charge(2) << "\n";
    std::cout << "5. charge(2.0f) [float->dbl]= " << charge(2.0f) << "\n";
    std::cout << "6. charge(p1) [Parcel]      = " << charge(p1) << "\n";
    return 0;
}
