#include <iostream>
#include <string>

enum class StaffType { Professor, LabAssistant, GuestFaculty };

struct MonolithicStaff {
    StaffType type;
    std::string name;
    int id;
    double basic = 0.0;
    double daRate = 0.42;
    double research = 0.0;
    double hours = 0.0;
    double rate = 0.0;

    double pay() const {
        switch (type) {
            case StaffType::Professor:    return basic + basic * daRate + research;
            case StaffType::LabAssistant: return basic + basic * daRate;
            case StaffType::GuestFaculty: return hours * rate;
        }
        return 0.0;
    }
};

int main() {
    MonolithicStaff m{StaffType::GuestFaculty, "Ananya R", 303, 0.0, 0.42, 0.0, 40.0, 1200.0};
    std::cout << "sizeof(MonolithicStaff) = " << sizeof(MonolithicStaff)
              << " bytes | pay = " << m.pay() << "\n";
    return 0;
}
