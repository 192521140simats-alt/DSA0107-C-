#include <iostream>

struct Bill {
    ~Bill() { std::cout << "~Bill "; }
    virtual double total() const = 0;
    void show() const { std::cout << total() << ' '; }
};

struct OPBill : Bill {
    double* extraResource;
    OPBill() : extraResource(new double[10]{500.0}) {}
    ~OPBill() { delete[] extraResource; std::cout << "~OPBill "; }
    double total() const override { return extraResource[0]; }
};

int main() {
    Bill* b = new OPBill;
    b->show();
    delete b;
    std::cout << '\n';
}
