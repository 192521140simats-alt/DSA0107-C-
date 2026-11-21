#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() { std::cout << "~Account()\n"; }
};

class SeniorAccount : public Account {
    double* history = new double[100];
public:
    double rate() const override { return 4.0; }
    ~SeniorAccount() override {
        std::cout << "~SeniorAccount()\n";
        delete[] history;
    }
};

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());

    for (const auto& a : accounts) {
        std::cout << a->rate() << "\n";
    }

    // Reference avoids object slicing
    SeniorAccount seniorObj;
    const Account& ref = seniorObj;
    std::cout << "Polymorphic ref rate (no slicing): " << ref.rate() << "\n";
    return 0;
}
