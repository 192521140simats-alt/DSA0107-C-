#include <iostream>
#include <string>

class Address {
    std::string city;
    int pin;
public:
    Address(std::string c, int p) : city(std::move(c)), pin(p) {
        std::cout << "[Ctor Address] ";
    }
    ~Address() { std::cout << "[Dtor Address] "; }
};

class Course {
    std::string code;
public:
    explicit Course(std::string c) : code(std::move(c)) {
        std::cout << "[Ctor Course] ";
    }
    ~Course() { std::cout << "[Dtor Course] "; }
};

class Person {
protected:
    std::string name;
    Address addr;
public:
    Person(std::string n, std::string city, int pin)
        : name(std::move(n)), addr(std::move(city), pin) {
        std::cout << "[Ctor Person] ";
    }
    virtual ~Person() { std::cout << "[Dtor Person] "; }
};

class Student : virtual public Person {
protected:
    Course enrolled;
public:
    Student(std::string n, std::string city, int pin, std::string courseCode)
        : Person(std::move(n), std::move(city), pin), enrolled(std::move(courseCode)) {
        std::cout << "[Ctor Student] ";
    }
    ~Student() override { std::cout << "[Dtor Student] "; }
};

class Staff : virtual public Person {
protected:
    std::string dept;
public:
    Staff(std::string n, std::string city, int pin, std::string d)
        : Person(std::move(n), std::move(city), pin), dept(std::move(d)) {
        std::cout << "[Ctor Staff] ";
    }
    ~Staff() override { std::cout << "[Dtor Staff] "; }
};

class TeachingAssistant : public Student, public Staff {
    std::string labSection;
public:
    TeachingAssistant(std::string n, std::string city, int pin,
                      std::string courseCode, std::string d, std::string sec)
        : Person(std::move(n), std::move(city), pin),
          Student("", "", 0, std::move(courseCode)),
          Staff("", "", 0, std::move(d)),
          labSection(std::move(sec)) {
        std::cout << "[Ctor TA] ";
    }
    ~TeachingAssistant() override { std::cout << "[Dtor TA] "; }
};

// Non-virtual experiment classes
class PersonNV {
    std::string name;
    Address addr;
public:
    PersonNV(std::string n, std::string c, int p) : name(std::move(n)), addr(std::move(c), p) {
        std::cout << "[Ctor PersonNV] ";
    }
    ~PersonNV() { std::cout << "[Dtor PersonNV] "; }
};
class StudentNV : public PersonNV {
    Course c;
public:
    StudentNV(std::string n, std::string city, int pin, std::string code)
        : PersonNV(std::move(n), std::move(city), pin), c(std::move(code)) {
        std::cout << "[Ctor StudentNV] ";
    }
    ~StudentNV() { std::cout << "[Dtor StudentNV] "; }
};
class StaffNV : public PersonNV {
    std::string dept;
public:
    StaffNV(std::string n, std::string city, int pin, std::string d)
        : PersonNV(std::move(n), std::move(city), pin), dept(std::move(d)) {
        std::cout << "[Ctor StaffNV] ";
    }
    ~StaffNV() { std::cout << "[Dtor StaffNV] "; }
};
class TeachingAssistantNV : public StudentNV, public StaffNV {
    std::string labSection;
public:
    TeachingAssistantNV(std::string n, std::string city, int pin,
                        std::string code, std::string d, std::string sec)
        : StudentNV(n, city, pin, std::move(code)),
          StaffNV(std::move(n), std::move(city), pin, std::move(d)),
          labSection(std::move(sec)) {
        std::cout << "[Ctor TA_NV] ";
    }
    ~TeachingAssistantNV() { std::cout << "[Dtor TA_NV] "; }
};

int main() {
    std::cout << "1) Student lifecycle:\n";
    { Student s("Arun", "Chennai", 600001, "DSA01"); }
    std::cout << "\n\n2) Staff lifecycle:\n";
    { Staff st("Meera", "Avadi", 600054, "CSE"); }
    std::cout << "\n\n3) TeachingAssistant (virtual base) lifecycle:\n";
    { TeachingAssistant ta("Tharika", "Chennai", 600001, "DSA01", "CSE", "L1"); }
    std::cout << "\n\n4) Experiment without virtual:\n";
    { TeachingAssistantNV tanv("Tharika", "Chennai", 600001, "DSA01", "CSE", "L1"); }
    std::cout << "\n\nsizeof(TeachingAssistant) virtual   : " << sizeof(TeachingAssistant) << " bytes\n";
    std::cout << "sizeof(TeachingAssistantNV) non-virt: " << sizeof(TeachingAssistantNV) << " bytes\n";
    return 0;
}
