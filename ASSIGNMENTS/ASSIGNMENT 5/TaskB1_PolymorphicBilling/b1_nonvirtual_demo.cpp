#include <iostream>
#include <string>

struct Bill {
    std::string patient;
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    double total() const { return 0.0; }
    virtual std::string type() const { return "Bill"; }
    void print() const {
        std::cout << type() << ' ' << patient << ": " << total() << '\n';
    }
};

struct OutPatient : Bill {
    double c, t;
    OutPatient(std::string p, double c, double t) : Bill(std::move(p)), c(c), t(t) {}
    double total() const { return c + t; }
    std::string type() const override { return "OP"; }
};

struct InPatient : Bill {
    int d; double r, s;
    InPatient(std::string p, int d, double r, double s) : Bill(std::move(p)), d(d), r(r), s(s) {}
    double total() const { return d * r + s; }
    std::string type() const override { return "IP"; }
};

int main() {
    Bill* bills[] = {new OutPatient("Ravi", 500, 1200), new InPatient("Meena", 3, 2500, 40000)};
    double sum = 0;
    for (Bill* b : bills) {
        b->print();
        sum += b->total();
    }
    std::cout << "Total " << sum << '\n';
    for (Bill* b : bills) delete b;
}
