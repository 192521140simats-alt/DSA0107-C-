#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string customer;
    std::string items[10];
    double prices[10];
    int n = 0;
    double discount = 0.0;

public:
    explicit Cart(std::string cust = "Guest") : customer(std::move(cust)) {}

    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double sum = 0.0;
        for (int i = 0; i < n; ++i) sum += prices[i];
        return sum * (100.0 - discount) / 100.0;
    }

    const std::string& getCustomer() const { return customer; }
};

int main() {
    std::cout << std::fixed << std::setprecision(2);

    // (a) Directly by object name
    Cart c1("Asha");
    c1.add("Apples", 150.0).add("Milk", 60.0).setDiscount(5.0);

    // (b) Through a pointer with ->
    Cart* p1 = &c1;
    p1->add("Bread", 40.0);

    // (c) Through a reference
    Cart c2("Bala");
    Cart& ref2 = c2;
    ref2.add("Rice", 500.0).add("Ghee", 300.0).setDiscount(10.0);

    // (d) Dynamically via new and released with delete
    Cart* dyn3 = new Cart("Chitra");
    dyn3->add("OliveOil", 950.0).add("Almonds", 450.0).setDiscount(15.0);

    std::cout << "(a/b) " << c1.getCustomer() << " total: " << p1->total() << "\n";
    std::cout << "(c)   " << ref2.getCustomer() << " total: " << ref2.total() << "\n";
    std::cout << "(d)   " << dyn3->getCustomer() << " total: " << dyn3->total() << "\n";

    // Task 5.2: Array of pointers to Cart objects -> find highest total via pointer arithmetic
    Cart* activeCarts[3] = { &c1, &c2, dyn3 };
    Cart** bestPtr = activeCarts;
    for (Cart** cur = activeCarts + 1; cur < activeCarts + 3; ++cur) {
        if ((*cur)->total() > (*bestPtr)->total()) {
            bestPtr = cur;
        }
    }
    std::cout << "Highest active cart: " << (*bestPtr)->getCustomer()
              << " -> Rs. " << (*bestPtr)->total() << "\n";

    delete dyn3;
    return 0;
}
