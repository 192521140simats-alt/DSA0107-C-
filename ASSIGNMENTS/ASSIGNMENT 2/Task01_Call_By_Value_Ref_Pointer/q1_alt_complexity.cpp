#include <iostream>
#include <string>

struct Student {
    int regNo;
    std::string name;
    long long hostelFee;
    double attendance;
    char roomBlock[32];
};

long long applyConcessionReturn(long long fee, int percent) {
    return fee - (fee * percent) / 100;
}

std::size_t sizeByValue(Student s) { return sizeof(s); }
std::size_t sizeByRef(Student& s) { return sizeof(&s); }
std::size_t sizeByConstRef(const Student& s) { return sizeof(&s); }

int main() {
    long long fee = 45000;
    fee = applyConcessionReturn(applyConcessionReturn(fee, 10), 15);
    std::cout << "Chained return fee (45000 -> -10% -> -15%): " << fee << "\n";

    Student st{192521140, "Tharika S", 45000, 96.5, "Block-A"};
    std::cout << "sizeof(Student) [copied if passed by value]: " << sizeof(Student) << " bytes\n";
    std::cout << "By value param size : " << sizeByValue(st) << " bytes\n";
    std::cout << "By ref param size   : " << sizeByRef(st) << " bytes (pointer/alias)\n";
    std::cout << "By const& param size: " << sizeByConstRef(st) << " bytes (pointer/alias)\n";
    return 0;
}
