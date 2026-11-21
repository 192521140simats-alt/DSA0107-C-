#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

class Bill {
protected:
    std::string billId;
    std::string patientName;
public:
    Bill(std::string id, std::string p) : billId(std::move(id)), patientName(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    const std::string& id() const noexcept { return billId; }
};

class InPatientBill : public Bill {
    double amount;
public:
    InPatientBill(std::string id, std::string p, double amt)
        : Bill(std::move(id), std::move(p)), amount(amt) {}
    double total() const override { return amount; }
    std::string type() const override { return "InPatient"; }
};

// Abstract Payer Base Class
class Payer {
public:
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double amountCovered(const Bill& bill) const = 0;
};

class SelfPay : public Payer {
public:
    std::string name() const override { return "SelfPay"; }
    double amountCovered(const Bill&) const override { return 0.0; }
};

class Insurance : public Payer {
    double coverLimit;
    double copayPercent;
public:
    Insurance(double limit, double copay) : coverLimit(limit), copayPercent(copay) {}
    std::string name() const override { return "Insurance"; }
    double amountCovered(const Bill& bill) const override {
        double eligible = bill.total() * (1.0 - copayPercent / 100.0);
        return (eligible < coverLimit) ? eligible : coverLimit;
    }
};

class GovernmentScheme : public Payer {
    double fixedCap;
public:
    explicit GovernmentScheme(double cap) : fixedCap(cap) {}
    std::string name() const override { return "GovernmentScheme"; }
    double amountCovered(const Bill& bill) const override {
        return (bill.total() < fixedCap) ? bill.total() : fixedCap;
    }
};

// A3.2: Open-Closed Extension — Added without modifying Bill or existing Payers
class CorporateTieUpPayer : public Payer {
    std::string companyName;
    double corporateCap;
    double discountPercent;
public:
    CorporateTieUpPayer(std::string comp, double cap, double disc)
        : companyName(std::move(comp)), corporateCap(cap), discountPercent(disc) {}
    std::string name() const override { return "CorporateTieUp(" + companyName + ")"; }
    double amountCovered(const Bill& bill) const override {
        double payable = bill.total() * (1.0 - discountPercent / 100.0);
        return (payable <= corporateCap) ? payable : corporateCap;
    }
};

int main() {
    InPatientBill sampleBill("B301", "Meena", 47500.0);
    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<Insurance>(30000.0, 10.0));
    payers.push_back(std::make_unique<GovernmentScheme>(20000.0));
    payers.push_back(std::make_unique<CorporateTieUpPayer>("TechCorp", 45000.0, 15.0));

    std::cout << "=== TASK A3: ABSTRACT PAYER HIERARCHY & EXTENSIBILITY ===\n";
    std::cout << "Evaluating Bill [" << sampleBill.id() << "] (" << sampleBill.type()
              << ") = Rs." << std::fixed << std::setprecision(2) << sampleBill.total() << "\n";
    std::cout << "--------------------------------------------------------------------------\n";
    for (const auto& p : payers) {
        double covered = p->amountCovered(sampleBill);
        double patientBalance = sampleBill.total() - covered;
        std::cout << "Payer: " << std::setw(24) << std::left << p->name()
                  << " | Covered: Rs." << std::setw(9) << covered
                  << " | Patient Balance: Rs." << patientBalance << "\n";
    }
    return 0;
}
