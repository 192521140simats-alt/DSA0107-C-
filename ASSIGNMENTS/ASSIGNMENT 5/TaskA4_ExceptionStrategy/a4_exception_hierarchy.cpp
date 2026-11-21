#include <iostream>
#include <stdexcept>
#include <string>
#include <new>

// Custom Hospital Exception Hierarchy rooted in std::exception -> std::runtime_error
class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class NegativeChargeError : public BillingError {
public:
    explicit NegativeChargeError(const std::string& msg)
        : BillingError("NegativeChargeError: " + msg) {}
};

class ClaimError : public BillingError {
public:
    explicit ClaimError(const std::string& msg)
        : BillingError("ClaimError: " + msg) {}
};

class UnknownPackageError : public BillingError {
public:
    explicit UnknownPackageError(const std::string& msg)
        : BillingError("UnknownPackageError: " + msg) {}
};

class PatientRecordMissingError : public BillingError {
public:
    explicit PatientRecordMissingError(const std::string& msg)
        : BillingError("PatientRecordMissingError: " + msg) {}
};

class BillRecord {
    std::string patientId;
    double amount;
public:
    // Constructor may throw on invalid invariants
    BillRecord(std::string pid, double amt) : patientId(std::move(pid)), amount(amt) {
        if (patientId.empty()) {
            throw PatientRecordMissingError("Patient ID cannot be empty");
        }
        if (amount < 0.0) {
            throw NegativeChargeError("Charge amount cannot be negative (" + std::to_string(amount) + ")");
        }
    }

    // Destructor and getters are noexcept
    ~BillRecord() noexcept = default;
    const std::string& getPatientId() const noexcept { return patientId; }
    double getAmount() const noexcept { return amount; }
};

void verifyClaim(const BillRecord& rec, double coverLimit, const std::string& pkg) {
    if (pkg != "PKG-GEN" && pkg != "PKG-SURG") {
        throw UnknownPackageError("Unknown package code '" + pkg + "'");
    }
    if (rec.getAmount() > coverLimit) {
        throw ClaimError("Bill Rs." + std::to_string(rec.getAmount()) +
                         " exceeds policy cover Rs." + std::to_string(coverLimit));
    }
}

int main() {
    std::cout << "=== TASK A4: EXCEPTION HIERARCHY & NOEXCEPT SPECIFICATIONS ===\n";
    std::cout << "noexcept(BillRecord::getAmount()): " << std::boolalpha
              << noexcept(std::declval<BillRecord>().getAmount()) << "\n";
    std::cout << "noexcept(~BillRecord())          : "
              << std::is_nothrow_destructible<BillRecord>::value << "\n\n";

    // Test 1: Missing patient record
    try {
        BillRecord r("", 1200.0);
    } catch (const BillingError& e) {
        std::cout << "[Caught 1] " << e.what() << "\n";
    }

    // Test 2: Negative charge
    try {
        BillRecord r("P101", -500.0);
    } catch (const BillingError& e) {
        std::cout << "[Caught 2] " << e.what() << "\n";
    }

    // Test 3: Unknown package
    try {
        BillRecord r("P102", 15000.0);
        verifyClaim(r, 25000.0, "PKG-INVALID");
    } catch (const BillingError& e) {
        std::cout << "[Caught 3] " << e.what() << "\n";
    }

    // Test 4: Claim above cover
    try {
        BillRecord r("P103", 45000.0);
        verifyClaim(r, 30000.0, "PKG-SURG");
    } catch (const BillingError& e) {
        std::cout << "[Caught 4] " << e.what() << "\n";
    }

    return 0;
}
