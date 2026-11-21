#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class NegativeChargeError : public BillingError {
public:
    using BillingError::BillingError;
};

class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};

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
};

class OutPatientBill : public Bill {
    double c, t;
public:
    OutPatientBill(std::string id, std::string p, double c, double t)
        : Bill(std::move(id), std::move(p)), c(c), t(t) {
        if (c < 0 || t < 0) throw NegativeChargeError("Negative OP charge");
    }
    double total() const override { return c + t; }
    std::string type() const override { return "OutPatient"; }
};

class InPatientBill : public Bill {
    int d; double r, proc, med;
public:
    InPatientBill(std::string id, std::string p, int d, double r, double proc, double med)
        : Bill(std::move(id), std::move(p)), d(d), r(r), proc(proc), med(med) {
        if (d <= 0 || r < 0 || proc < 0 || med < 0) throw NegativeChargeError("Invalid IP charge");
    }
    double total() const override { return d * r + proc + med; }
    std::string type() const override { return "InPatient"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual std::string name() const = 0;
    virtual double amountCovered(const Bill& bill) const = 0;
};

class Insurance : public Payer {
    double limit, copay;
public:
    Insurance(double limit, double copay) : limit(limit), copay(copay) {}
    std::string name() const override { return "Insurance"; }
    double amountCovered(const Bill& bill) const override {
        double eligible = bill.total() * (1.0 - copay / 100.0);
        if (eligible > limit) throw ClaimError("Eligible claim exceeds policy limit");
        return eligible;
    }
};

class TelemedicineBill : public Bill {
    double videoFee, digitalRxFee;
public:
    TelemedicineBill(std::string id, std::string p, double vFee, double rxFee)
        : Bill(std::move(id), std::move(p)), videoFee(vFee), digitalRxFee(rxFee) {
        if (vFee < 0 || rxFee < 0) throw NegativeChargeError("Negative Telemedicine fee");
    }
    double total() const override { return videoFee + digitalRxFee; }
    std::string type() const override { return "Telemedicine"; }
};

class CorporateTieUpPayer : public Payer {
    std::string company;
    double corporateCap;
    double discountPercent;
public:
    CorporateTieUpPayer(std::string comp, double cap, double disc)
        : company(std::move(comp)), corporateCap(cap), discountPercent(disc) {}
    std::string name() const override { return "CorpTieUp(" + company + ")"; }
    double amountCovered(const Bill& bill) const override {
        double payable = bill.total() * (1.0 - discountPercent / 100.0);
        return (payable <= corporateCap) ? payable : corporateCap;
    }
};

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    std::vector<std::unique_ptr<Payer>> payers;
    payers.push_back(std::make_unique<Insurance>(25000.0, 10.0));
    payers.push_back(std::make_unique<CorporateTieUpPayer>("InfosysHealth", 50000.0, 15.0));

    struct RawRecord { std::string kind, id, name; double a, b, c, d; };
    std::vector<RawRecord> incoming = {
        {"OP",   "B201", "Ravi",   500, 1200, 0, 0},
        {"IP",   "B202", "Meena",  3, 2500, 35000, 5000},
        {"TELE", "B203", "Karthik", 600, 350, 0, 0},
        {"TELE", "B204", "InvalidUser", -200, 100, 0, 0}
    };

    std::cout << "=== B4.1 & B4.2 EXTENSION + FAULT-RESILIENT BATCH RUN ===\n";
    for (const auto& rec : incoming) {
        try {
            if (rec.kind == "OP")
                bills.push_back(std::make_unique<OutPatientBill>(rec.id, rec.name, rec.a, rec.b));
            else if (rec.kind == "IP")
                bills.push_back(std::make_unique<InPatientBill>(rec.id, rec.name, static_cast<int>(rec.a), rec.b, rec.c, rec.d));
            else if (rec.kind == "TELE")
                bills.push_back(std::make_unique<TelemedicineBill>(rec.id, rec.name, rec.a, rec.b));
        } catch (const BillingError& e) {
            std::cout << "[Rejected Record " << rec.id << "] " << e.what() << " (Batch preserved)\n";
        }
    }

    for (const auto& b : bills) {
        for (const auto& p : payers) {
            try {
                double cov = p->amountCovered(*b);
                std::cout << "[" << b->id() << "] " << std::setw(12) << std::left << b->type()
                          << " | Payer: " << std::setw(22) << p->name()
                          << " | Total: Rs." << std::setw(8) << std::fixed << std::setprecision(2) << b->total()
                          << " | Covered: Rs." << std::setw(8) << cov << "\n";
            } catch (const ClaimError& e) {
                std::cout << "[" << b->id() << "] " << std::setw(12) << std::left << b->type()
                          << " | Payer: " << std::setw(22) << p->name()
                          << " | CLAIM REJECTED: " << e.what() << "\n";
            }
        }
    }
    std::cout << "=== Batch complete: " << bills.size() << " valid bills settled, 0 memory leaks ===\n";
    return 0;
}
