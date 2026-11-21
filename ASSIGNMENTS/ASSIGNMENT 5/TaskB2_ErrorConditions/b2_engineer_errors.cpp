#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <new>
#include <limits>
#include <memory>

class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class NegativeChargeError : public BillingError {
public:
    explicit NegativeChargeError(const std::string& msg) : BillingError("NegativeChargeError: " + msg) {}
};

class ClaimError : public BillingError {
public:
    explicit ClaimError(const std::string& msg) : BillingError("ClaimError: " + msg) {}
};

class UnknownPackageError : public BillingError {
public:
    explicit UnknownPackageError(const std::string& msg) : BillingError("UnknownPackageError: " + msg) {}
};

struct TransactionGuard {
    std::string label;
    explicit TransactionGuard(std::string l) : label(std::move(l)) {
        std::cout << "  [RAII Acquire] " << label << "\n";
    }
    ~TransactionGuard() {
        std::cout << "  [RAII Destroy] " << label << " safely released\n";
    }
};

double lookupPackageRate(const std::string& code) {
    if (code == "PKG-CAT") return 22000.0;
    if (code == "PKG-APP") return 45000.0;
    throw UnknownPackageError("Unrecognized package code '" + code + "'");
}

void executeCase(int caseId, const std::string& mode, const std::string& arg1, double arg2) {
    std::cout << "--- Test Case " << caseId << " (" << mode << ") ---\n";
    try {
        TransactionGuard guard("BillSession#" + std::to_string(caseId));
        if (mode == "NEGATIVE_CHARGE") {
            double val = std::stod(arg1);
            if (val < 0) throw NegativeChargeError("Consultation fee cannot be " + std::to_string(val));
        } else if (mode == "CLAIM_OVER_COVER") {
            double billed = std::stod(arg1);
            if (billed > arg2) throw ClaimError("Billed " + std::to_string(billed) + " exceeds cover " + std::to_string(arg2));
        } else if (mode == "UNKNOWN_PACKAGE") {
            double rate = lookupPackageRate(arg1);
            std::cout << "  Package rate: " << rate << "\n";
        } else if (mode == "BAD_TEXT_NUMBER") {
            double parsed = std::stod(arg1);
            std::cout << "  Parsed: " << parsed << "\n";
        } else if (mode == "FORCE_BAD_ALLOC") {
            std::size_t huge = std::numeric_limits<std::size_t>::max() / sizeof(double);
            double* arr = new double[huge];
            delete[] arr;
        } else if (mode == "UNKNOWN_THROW") {
            throw 999;
        }
    } catch (const BillingError& e) {
        std::cout << "  [Caught Domain Error] " << e.what() << "\n";
    } catch (const std::bad_alloc& e) {
        std::cout << "  [Caught Memory Error] std::bad_alloc (" << e.what() << ")\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "  [Caught Parse Error] std::invalid_argument (" << e.what() << ")\n";
    } catch (...) {
        std::cout << "  [Caught Catch-All (...)] Non-standard exception intercepted; loop continues safely.\n";
    }
}

int main() {
    executeCase(1, "NEGATIVE_CHARGE", "-450.0", 0);
    executeCase(2, "CLAIM_OVER_COVER", "75000.0", 50000.0);
    executeCase(3, "UNKNOWN_PACKAGE", "PKG-XYZ", 0);
    executeCase(4, "BAD_TEXT_NUMBER", "ABC_FEE", 0);
    executeCase(5, "FORCE_BAD_ALLOC", "0", 0);
    executeCase(6, "UNKNOWN_THROW", "0", 0);
    std::cout << "=== All 6 fault scenarios survived with zero resource leaks ===\n";
    return 0;
}
