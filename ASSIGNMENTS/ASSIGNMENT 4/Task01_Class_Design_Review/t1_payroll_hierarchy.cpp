#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

class Staff {
protected:
    std::string name;
    int staffId;

public:
    Staff(std::string staffName, int id)
        : name(std::move(staffName)), staffId(id) {}

    virtual ~Staff() = default;

    int getId() const { return staffId; }
    const std::string& getName() const { return name; }
    virtual std::string role() const = 0;
    virtual double pay() const = 0;
};

class SalariedStaff : public Staff {
protected:
    static constexpr double DA_RATE = 0.42;
    double basicPay;

public:
    SalariedStaff(std::string staffName, int id, double basic)
        : Staff(std::move(staffName), id), basicPay(basic) {}

    double computeDearnessAllowance() const {
        return basicPay * DA_RATE;
    }
};

class Professor : public SalariedStaff {
private:
    double researchAllowance;

public:
    Professor(std::string staffName, int id, double basic, double research)
        : SalariedStaff(std::move(staffName), id, basic),
          researchAllowance(research) {}

    std::string role() const override { return "Professor"; }
    double pay() const override {
        return basicPay + computeDearnessAllowance() + researchAllowance;
    }
};

class LabAssistant : public SalariedStaff {
public:
    LabAssistant(std::string staffName, int id, double basic)
        : SalariedStaff(std::move(staffName), id, basic) {}

    std::string role() const override { return "LabAssistant"; }
    double pay() const override {
        return basicPay + computeDearnessAllowance();
    }
};

class GuestFaculty : public Staff {
private:
    double hoursWorked;
    double hourlyRate;

public:
    GuestFaculty(std::string staffName, int id, double hours, double rate)
        : Staff(std::move(staffName), id),
          hoursWorked(hours), hourlyRate(rate) {}

    std::string role() const override { return "GuestFaculty"; }
    double pay() const override {
        return hoursWorked * hourlyRate;
    }
};

// Demonstrating extensibility without modifying Staff, SalariedStaff, or existing classes
class VisitingResearcher : public SalariedStaff {
private:
    double grantStipend;

public:
    VisitingResearcher(std::string staffName, int id, double basic, double grant)
        : SalariedStaff(std::move(staffName), id, basic), grantStipend(grant) {}

    std::string role() const override { return "VisitingResearcher"; }
    double pay() const override {
        return basicPay + computeDearnessAllowance() + grantStipend;
    }
};

int main() {
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Dr. Meenakshi", 101, 80000.0, 15000.0));
    payroll.push_back(std::make_unique<LabAssistant>("Suresh K", 202, 35000.0));
    payroll.push_back(std::make_unique<GuestFaculty>("Ananya R", 303, 40.0, 1200.0));
    payroll.push_back(std::make_unique<VisitingResearcher>("Dr. Karthik", 404, 60000.0, 10000.0));

    std::cout << std::fixed << std::setprecision(2);
    double totalPayroll = 0.0;
    for (const auto& member : payroll) {
        double p = member->pay();
        totalPayroll += p;
        std::cout << "[" << member->getId() << "] " << member->getName()
                  << " (" << member->role() << ") -> Pay: Rs. " << p << "\n";
    }
    std::cout << "Total Monthly Payroll: Rs. " << totalPayroll << "\n";
    return 0;
}
