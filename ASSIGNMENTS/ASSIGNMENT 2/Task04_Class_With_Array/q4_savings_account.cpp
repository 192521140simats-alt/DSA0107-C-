#include <iostream>
#include <string>

class SavingsAccount {
private:
    static const int MAX_TX = 10;
    int accountNumber;
    double balance;
    double transactions[MAX_TX];
    int count;

    void recordTransaction(double signedAmt) {
        if (count < MAX_TX) {
            transactions[count++] = signedAmt;
        } else {
            for (int i = 1; i < MAX_TX; ++i) {
                transactions[i - 1] = transactions[i];
            }
            transactions[MAX_TX - 1] = signedAmt;
        }
    }

public:
    SavingsAccount(int accNo, double initialBalance)
        : accountNumber(accNo), balance(initialBalance), count(0) {
        for (int i = 0; i < MAX_TX; ++i) transactions[i] = 0.0;
    }

    void deposit(double amount) {
        if (amount > 0.0) {
            balance += amount;
            recordTransaction(amount);
        }
    }

    bool withdraw(double amount);
    void miniStatement() const;
};

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0.0 || amount > balance) {
        return false;
    }
    balance -= amount;
    recordTransaction(-amount);
    return true;
}

void SavingsAccount::miniStatement() const {
    std::cout << "Account #" << accountNumber
              << " | Balance: " << balance
              << " | Last " << count << " Transactions: ";
    for (int i = 0; i < count; ++i) {
        std::cout << (transactions[i] >= 0 ? "+" : "") << transactions[i]
                  << (i + 1 < count ? ", " : "");
    }
    std::cout << "\n";
}

int main() {
    SavingsAccount acc(1001, 5000.0);
    for (int i = 1; i <= 12; ++i) {
        if (i % 3 == 0) {
            acc.withdraw(200.0 * i);
        } else {
            acc.deposit(100.0 * i);
        }
    }
    acc.miniStatement();
    return 0;
}
