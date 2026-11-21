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
    Bill(std::string id, std::string patient)
        : billId(std::move(id)), patientName(std::move(patient)) {}
    virtual ~Bill() = default;

    virtual double total() const = 0;
    virtual std::string type() const = 0;

    const std::string& id() const noexcept { return billId; }
    const std::string& patient() const noexcept { return patientName; }

    virtual void print() const {
        std::cout << "[" << billId << "] " << std::setw(15) << std::left << type()
                  << " | Patient: " << std::setw(10) << patientName
                  << " | Total: Rs." << std::fixed << std::setprecision(2) << total() << "\n";
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

double computeDailyBillTotal(const std::vector<std::unique_ptr<Bill>>& bills) {
    double grandTotal = 0.0;
    for (const auto& b : bills) {
        if (b) {
            b->print();
            grandTotal += b->total();
        }
    }
    return grandTotal;
}

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatientBill>("B101", "Ravi", 500.0, 1200.0));
    bills.push_back(std::make_unique<InPatientBill>("B102", "Meena", 3, 2500.0, 35000.0, 5000.0));
    bills.push_back(std::make_unique<DayCareSurgeryBill>("B103", "Arjun", "PKG-CAT", 22000.0));
    bills.push_back(std::make_unique<EmergencyBill>("B104", "Priya", 3000.0, 1500.0, 4));

    std::cout << "=== TASK A1: POLYMORPHIC BILL HIERARCHY & DAILY TOTAL ===\n";
    double dailySum = computeDailyBillTotal(bills);
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "Grand Daily Total across " << bills.size() << " bills: Rs."
              << std::fixed << std::setprecision(2) << dailySum << "\n";
    return 0;
}
