#include <iostream>
#include <chrono>
#include <algorithm>

class LegacySavingsAccount {
private:
    static const int MAX_TX = 10;
    int accNo;
    double balance;
    double tx[MAX_TX];
    int count;

    void pushTx(double amt) {
        if (count < MAX_TX) {
            tx[count++] = amt;
        } else {
            for (int i = 1; i < MAX_TX; ++i) tx[i - 1] = tx[i];
            tx[MAX_TX - 1] = amt;
        }
    }

public:
    LegacySavingsAccount(int id, double bal) : accNo(id), balance(bal), count(0) {
        for (int i = 0; i < MAX_TX; ++i) tx[i] = 0.0;
    }
    void deposit(double amt) { balance += amt; pushTx(amt); }
    double getBalance() const { return balance; }
    int storedCount() const { return count; }
    double latestTx() const { return count > 0 ? tx[count - 1] : 0.0; }
};

class RedesignedSavingsAccount {
private:
    int accNo;
    double balance;
    int capacity;
    double* ring;
    int head;
    int sz;

    void pushTx(double amt) {
        if (sz < capacity) {
            ring[(head + sz) % capacity] = amt;
            ++sz;
        } else {
            ring[head] = amt;
            head = (head + 1) % capacity;
        }
    }

public:
    explicit RedesignedSavingsAccount(int id, double bal, int stmtCapacity = 50)
        : accNo(id), balance(bal), capacity(stmtCapacity > 0 ? stmtCapacity : 1),
          ring(new double[capacity]), head(0), sz(0) {
        for (int i = 0; i < capacity; ++i) ring[i] = 0.0;
    }

    ~RedesignedSavingsAccount() { delete[] ring; }

    RedesignedSavingsAccount(const RedesignedSavingsAccount& other)
        : accNo(other.accNo), balance(other.balance), capacity(other.capacity),
          ring(new double[other.capacity]), head(other.head), sz(other.sz) {
        for (int i = 0; i < capacity; ++i) ring[i] = other.ring[i];
    }

    RedesignedSavingsAccount& operator=(const RedesignedSavingsAccount& other) {
        if (this != &other) {
            double* nextRing = new double[other.capacity];
            for (int i = 0; i < other.capacity; ++i) nextRing[i] = other.ring[i];
            delete[] ring;
            ring = nextRing;
            accNo = other.accNo;
            balance = other.balance;
            capacity = other.capacity;
            head = other.head;
            sz = other.sz;
        }
        return *this;
    }

    void deposit(double amt) { balance += amt; pushTx(amt); }
    double getBalance() const { return balance; }
    int storedCount() const { return sz; }
    int getCapacity() const { return capacity; }
    double latestTx() const {
        if (sz == 0) return 0.0;
        return ring[(head + sz - 1) % capacity];
    }
};

int main() {
    const int OPS = 500000;
    LegacySavingsAccount leg(2001, 10000.0);
    RedesignedSavingsAccount red(2001, 10000.0, 50);

    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= OPS; ++i) leg.deposit(10.0);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= OPS; ++i) red.deposit(10.0);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto usLegacy = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    auto usRedes  = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cout << "Validation (500,000 deposits of +10.0):\n";
    std::cout << "  Legacy     -> balance=" << leg.getBalance()
              << ", stored=" << leg.storedCount() << ", latest=" << leg.latestTx()
              << ", time=" << usLegacy << " us\n";
    std::cout << "  Redesigned -> balance=" << red.getBalance()
              << ", stored=" << red.storedCount() << "/" << red.getCapacity()
              << ", latest=" << red.latestTx() << ", time=" << usRedes << " us\n";
    return 0;
}
