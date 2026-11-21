#include <iostream>
#include <iomanip>

// 1. Procedural style with free functions and separate state
bool procCanTravel(long long balancePaise, long long farePaise, long long minKeepPaise) {
    return farePaise >= 0 && (balancePaise - farePaise) >= minKeepPaise;
}

bool procDeduct(long long& balancePaise, long long farePaise, long long minKeepPaise) {
    if (!procCanTravel(balancePaise, farePaise, minKeepPaise)) return false;
    balancePaise -= farePaise;
    return true;
}

// 2. Object-Oriented SmartCard encapsulating balancePaise
class SmartCard {
private:
    long long balancePaise;
    long long minRemainingPaise;

public:
    SmartCard(long long initialPaise, long long minKeepPaise = 5000)
        : balancePaise(initialPaise >= 0 ? initialPaise : 0),
          minRemainingPaise(minKeepPaise) {}

    bool canTravel(long long farePaise) const {
        return farePaise >= 0 && (balancePaise - farePaise) >= minRemainingPaise;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }

    long long balance() const { return balancePaise; }
};

int main() {
    long long pBal = 9000;
    std::cout << "Procedural deduct 3600: " << procDeduct(pBal, 3600, 5000)
              << " | bal=" << pBal << "\n";

    SmartCard card(9000, 5000);
    std::cout << "OOP deduct 3600: " << card.deduct(3600)
              << " | bal=" << card.balance() << "\n";
    std::cout << "OOP deduct 1000: " << card.deduct(1000)
              << " | bal=" << card.balance() << "\n";
    return 0;
}
