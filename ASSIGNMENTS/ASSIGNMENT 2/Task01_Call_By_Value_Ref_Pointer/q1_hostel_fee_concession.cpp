#include <iostream>
#include <iomanip>

void applyFeeByValue(long long fee, int percent) {
    fee = fee - (fee * percent) / 100; // modifies only local stack copy
}

void applyFeeByReference(long long& fee, int percent) {
    fee = fee - (fee * percent) / 100; // modifies caller's variable directly via alias
}

void applyFeeByPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee = *fee - (*fee * percent) / 100; // dereferences pointer to modify caller's variable
    }
}

long long previewConcession(const long long& fee, int percent) {
    return fee - (fee * percent) / 100;
}

int main() {
    long long initialFee = 50000;
    long long f1 = initialFee;
    long long f2 = initialFee;
    long long f3 = initialFee;

    applyFeeByValue(f1, 10);      // Merit 10% -> stays 50000
    applyFeeByReference(f2, 15);  // Sports 15% -> becomes 42500
    applyFeeByPointer(&f3, 25);   // Single parent 25% -> becomes 37500

    std::cout << "Initial Fee          : " << initialFee << "\n";
    std::cout << "After By Value (10%) : " << f1 << "\n";
    std::cout << "After By Ref (15%)   : " << f2 << "\n";
    std::cout << "After By Ptr (25%)   : " << f3 << "\n";
    std::cout << "Preview Only (25%)   : " << previewConcession(f2, 25)
              << " (f2 still " << f2 << ")\n";
    return 0;
}
