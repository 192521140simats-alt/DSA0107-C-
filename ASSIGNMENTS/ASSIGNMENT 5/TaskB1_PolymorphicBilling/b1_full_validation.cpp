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
    const std::string& patient() const noexcept { return patientName; }
    virtual void print() const {
        std::cout << "[" << billId << "] " << std::setw(14) << std::left << type()
                  << " | Patient: " << std::setw(10) << patientName
                  << " | Billed: Rs." << std::fixed << std::setprecision(2) << total();
    }
};

class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(std::string id, std::string p, double c, double t)
        : Bill(std::move(id), std::move(p)), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OutPatient"; }
};

class InPatientBill : public Bill {
    int days;
    double roomPerDay, procedures, medicines;
public:
    InPatientBill(std::string id, std::string p, int d, double r, double proc, double med)
        : Bill(std::move(id), std::move(p)), days(d), roomPerDay(r), procedures(proc), medicines(med) {}
    double total() const override { return days * roomPerDay + procedures + medicines; }
    std::string type() const override { return "InPatient"; }
};

class DayCareSurgeryBill : public Bill {
    std::string packageCode;
    double packageRate;
public:
    DayCareSurgeryBill(std::string id, std::string p, std::string code, double rate)
        : Bill(std::move(id), std::move(p)), packageCode(std::move(code)), packageRate(rate) {}
    double total() const override { return packageRate; }
    std::string type() const override { return "DayCareSurgery"; }
};

class EmergencyBill : public Bill {
    double baseCharge, hourlyRate;
    int hours;
public:
    EmergencyBill(std::string id, std::string p, double base, double hrRate, int hrs)
        : Bill(std::move(id), std::move(p)), baseCharge(base), hourlyRate(hrRate), hours(hrs) {}
    double total() const override { return baseCharge + hourlyRate * hours; }
    std::string type() const override { return "Emergency"; }
};

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
    std::string name() const override { return "GovtScheme"; }
    double amountCovered(const Bill& bill) const override {
        return (bill.total() < fixedCap) ? bill.total() : fixedCap;
    }
};

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("B101", "Ravi", 500.0, 1200.0));
    bills.push_back(std::make_unique<InPatientBill>("B102", "Meena", 3, 2500.0, 35000.0, 5000.0));
    bills.push_back(std::make_unique<DayCareSurgeryBill>("B103", "Arjun", "PKG-CAT", 22000.0));
    bills.push_back(std::make_unique<EmergencyBill>("B104", "Priya", 3000.0, 1500.0, 4));

    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<SelfPay>());
    payers.push_back(std::make_unique<Insurance>(30000.0, 10.0));
    payers.push_back(std::make_unique<GovernmentScheme>(20000.0));

    double grandTotal = 0.0;
    std::cout << "=== B1.1 POLYMORPHIC BILLING & PAYER SETTLEMENT MATRIX ===\n";
    for (const auto& b : bills) {
        grandTotal += b->total();
        for (const auto& p : payers) {
            double covered = p->amountCovered(*b);
            double patientDue = b->total() - covered;
            b->print();
            std::cout << " | Payer: " << std::setw(10) << p->name()
                      << " | Covered: Rs." << std::setw(8) << covered
                      << " | PatientDue: Rs." << std::setw(8) << patientDue << "\n";
        }
        std::cout << "----------------------------------------------------------------------------------------------------\n";
    }
    std::cout << "Daily Gross Billed Total (4 Bills): Rs." << grandTotal << "\n";
    return 0;
}
