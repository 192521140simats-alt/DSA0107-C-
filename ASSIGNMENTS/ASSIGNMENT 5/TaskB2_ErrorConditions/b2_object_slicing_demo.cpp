#include <iostream>
#include <stdexcept>

class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

void inner() {
    throw ClaimError("exceeds cover");
}

void rethrowByValue() {
    try {
        inner();
    } catch (std::runtime_error e) {
        std::cout << "audit: " << e.what() << '\n';
        throw e; // SLICES ClaimError into std::runtime_error!
    }
}

int main() {
    try {
        rethrowByValue();
    } catch (const ClaimError& e) {
        std::cout << "claim rejected: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cout << "error (sliced to base): " << e.what() << '\n';
    }
}
