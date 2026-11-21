#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int age;
public:
    Person(const std::string& n, int a) : name(n), age(a) {}
};

class Address {
    std::string city;
    int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class StudentSwapped : public Person {
    long long regNo;
    Address home;
public:
    // Deliberately swapped order (home before regNo) to observe -Wreorder warning
    StudentSwapped(const std::string& n, int a, long long r, const std::string& c, int p)
        : Person(n, a), home(c, p), regNo(r) {}

    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") " << home.str() << '\n';
    }
};

int main() {
    StudentSwapped s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();
    return 0;
}
