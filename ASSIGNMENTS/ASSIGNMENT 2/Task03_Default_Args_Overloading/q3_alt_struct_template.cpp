#include <iostream>

struct ChargeRequest {
    double weightKg = 0.0;
    bool express = false;
    bool insured = false;
    bool fragileHandling = false;
};

double computeCharge(const ChargeRequest& req) {
    double total = 40.0 + req.weightKg * 15.0;
    if (req.express) total += 60.0;
    if (req.insured) total += 35.0;
    if (req.fragileHandling) total += 25.0;
    return total;
}

template <typename T>
double chargeUnit(T val, bool express = false) {
    return 40.0 + static_cast<double>(val) * 15.0 + (express ? 60.0 : 0.0);
}

int main() {
    ChargeRequest req{2.0, true, false, true};
    std::cout << "Struct request total : " << computeCharge(req) << "\n";
    std::cout << "Template charge(2.0) : " << chargeUnit(2.0) << "\n";
    std::cout << "Template charge(2)   : " << chargeUnit(2) << "\n";
    return 0;
}
