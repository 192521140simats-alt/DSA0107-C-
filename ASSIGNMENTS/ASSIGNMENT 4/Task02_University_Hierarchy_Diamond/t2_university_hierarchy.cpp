#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(std::string n = "", int pid = 0, std::string ph = "")
        : name(std::move(n)), id(pid), phone(std::move(ph)) {}
    virtual ~Person() = default;

    const std::string& getName() const { return name; }
    int getId() const { return id; }
    const std::string& getPhone() const { return phone; }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(std::string n, int pid, std::string ph, std::string prog, double gpa)
        : Person(std::move(n), pid, std::move(ph)),
          programme(std::move(prog)), cgpa(gpa) {}
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(std::string n, int pid, std::string ph, std::string dept, double sal)
        : Person(std::move(n), pid, std::move(ph)),
          department(std::move(dept)), salary(sal) {}
};

class TeachingAssistant : public Student, public Staff {
private:
    std::string assignedCourse;

public:
    TeachingAssistant(std::string n, int pid, std::string ph,
                      std::string prog, double gpa,
                      std::string dept, double sal, std::string course)
        : Person(std::move(n), pid, std::move(ph)),
          Student("", 0, "", std::move(prog), gpa),
          Staff("", 0, "", std::move(dept), sal),
          assignedCourse(std::move(course)) {}

    void display() const {
        std::cout << "TA: " << name << " (ID: " << id << ", Phone: " << phone
                  << ") | Prog: " << programme << " (CGPA: " << cgpa
                  << ") | Dept: " << department << ", Stipend: " << salary
                  << ", Course: " << assignedCourse << "\n";
    }
};

class ResearchScholar : public Student {
private:
    std::string fellowshipAgency;
    double fellowshipAmount;

public:
    ResearchScholar(std::string n, int pid, std::string ph,
                    std::string prog, double gpa,
                    std::string agency, double amount)
        : Person(std::move(n), pid, std::move(ph)),
          Student("", 0, "", std::move(prog), gpa),
          fellowshipAgency(std::move(agency)), fellowshipAmount(amount) {}

    void display() const {
        std::cout << "Scholar: " << name << " (ID: " << id
                  << ") | Prog: " << programme << " | Fellowship: "
                  << fellowshipAgency << " (Rs. " << fellowshipAmount << ")\n";
    }
};

// Alternative composition design for comparison
class ComposedTA {
private:
    Student studentPart;
    Staff staffPart;

public:
    ComposedTA(std::string n, int pid, std::string ph,
               std::string prog, double gpa, std::string dept, double sal)
        : studentPart(n, pid, ph, std::move(prog), gpa),
          staffPart(std::move(n), pid, std::move(ph), std::move(dept), sal) {}

    const std::string& getName() const { return studentPart.getName(); }
};

int main() {
    TeachingAssistant ta("Tharika S", 192521140, "9876543210",
                         "B.Tech CSE", 9.42, "CSE", 18000.0, "DSA01");
    ResearchScholar rs("Divya M", 192521999, "9123456780",
                       "Ph.D. AI", 9.65, "DST-INSPIRE", 37000.0);
    ta.display();
    rs.display();
    std::cout << "sizeof(TeachingAssistant) [virtual base]: " << sizeof(TeachingAssistant) << " bytes\n";
    std::cout << "sizeof(ComposedTA) [two Person subobjects]: " << sizeof(ComposedTA) << " bytes\n";
    return 0;
}
