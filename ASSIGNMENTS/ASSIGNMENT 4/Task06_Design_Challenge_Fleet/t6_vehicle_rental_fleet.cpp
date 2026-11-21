#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

class ServiceDate {
    int day, month, year;
public:
    ServiceDate(int d = 1, int m = 1, int y = 2026) : day(d), month(m), year(y) {}
    std::string str() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }
};

class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(std::string reg, double rate)
        : regNo(std::move(reg)), dailyRate(rate) {}
    virtual ~Vehicle() = default;

    const std::string& getRegNo() const { return regNo; }
    bool isRented() const { return rented; }

    bool rentOut() {
        if (rented) return false;
        rented = true;
        return true;
    }

    double returnVehicle(int daysUsed, int lateDays, double energyOrFuelUnits) {
        rented = false;
        return computeCharge(daysUsed, lateDays, energyOrFuelUnits);
    }

    virtual std::string category() const = 0;
    virtual double computeCharge(int days, int lateDays, double units) const = 0;
    virtual void printSummary() const {
        std::cout << "[" << category() << "] Reg: " << regNo
                  << " | Rate/day: Rs. " << dailyRate
                  << " | Status: " << (rented ? "RENTED" : "AVAILABLE");
    }
};

class Bicycle : public Vehicle {
    bool hasGear;
public:
    Bicycle(std::string reg, double rate, bool gear)
        : Vehicle(std::move(reg), rate), hasGear(gear) {}

    std::string category() const override { return "Bicycle"; }
    double computeCharge(int days, int lateDays, double /*units*/) const override {
        return days * dailyRate + lateDays * (dailyRate * 1.5);
    }
    void printSummary() const override {
        Vehicle::printSummary();
        std::cout << " | Gear: " << (hasGear ? "Yes" : "No") << "\n";
    }
};

class MotorVehicle : public Vehicle {
protected:
    double energyLevelPct;
    ServiceDate nextService;

public:
    MotorVehicle(std::string reg, double rate, double levelPct, ServiceDate srv)
        : Vehicle(std::move(reg), rate), energyLevelPct(levelPct), nextService(srv) {}

    void printSummary() const override {
        Vehicle::printSummary();
        std::cout << " | Level: " << energyLevelPct << "% | NextService: " << nextService.str();
    }
};

class TwoWheeler : public MotorVehicle {
    double perLitreRate;
public:
    TwoWheeler(std::string reg, double rate, double fuelPct, ServiceDate srv, double fuelPrice)
        : MotorVehicle(std::move(reg), rate, fuelPct, srv), perLitreRate(fuelPrice) {}

    std::string category() const override { return "TwoWheeler"; }
    double computeCharge(int days, int lateDays, double litresUsed) const override {
        return days * dailyRate + litresUsed * perLitreRate + lateDays * 300.0;
    }
    void printSummary() const override {
        MotorVehicle::printSummary();
        std::cout << "\n";
    }
};

class Car : public MotorVehicle {
protected:
    int seats;
    double perLitreRate;

public:
    Car(std::string reg, double rate, double fuelPct, ServiceDate srv, int seatCap, double fuelPrice)
        : MotorVehicle(std::move(reg), rate, fuelPct, srv), seats(seatCap), perLitreRate(fuelPrice) {}

    std::string category() const override { return "Car"; }
    double computeCharge(int days, int lateDays, double litresUsed) const override {
        return days * dailyRate + litresUsed * perLitreRate + lateDays * 800.0;
    }
    void printSummary() const override {
        MotorVehicle::printSummary();
        std::cout << " | Seats: " << seats << "\n";
    }
};

class ElectricCar : public MotorVehicle {
    int seats;
    double batteryKWh;
    double perKWhRate;

public:
    ElectricCar(std::string reg, double rate, double chargePct, ServiceDate srv,
                int seatCap, double kwhCap, double kwhPrice)
        : MotorVehicle(std::move(reg), rate, chargePct, srv),
          seats(seatCap), batteryKWh(kwhCap), perKWhRate(kwhPrice) {}

    std::string category() const override { return "ElectricCar"; }
    double computeCharge(int days, int lateDays, double kwhUsed) const override {
        return days * dailyRate + kwhUsed * perKWhRate + lateDays * 900.0;
    }
    void printSummary() const override {
        MotorVehicle::printSummary();
        std::cout << " | Seats: " << seats << " | Battery: " << batteryKWh << " kWh\n";
    }
};

// Stage 5 Extension: New ElectricBus type added WITHOUT modifying any existing class
class ElectricBus : public MotorVehicle {
    int passengerCap;
    double batteryKWh;
    double perKWhRate;

public:
    ElectricBus(std::string reg, double rate, double chargePct, ServiceDate srv,
                int paxCap, double kwhCap, double kwhPrice)
        : MotorVehicle(std::move(reg), rate, chargePct, srv),
          passengerCap(paxCap), batteryKWh(kwhCap), perKWhRate(kwhPrice) {}

    std::string category() const override { return "ElectricBus"; }
    double computeCharge(int days, int lateDays, double kwhUsed) const override {
        return days * dailyRate + kwhUsed * perKWhRate + lateDays * 2500.0;
    }
    void printSummary() const override {
        MotorVehicle::printSummary();
        std::cout << " | PaxCap: " << passengerCap << " | Battery: " << batteryKWh << " kWh\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("CYC-01", 200.0, true));
    fleet.push_back(std::make_unique<TwoWheeler>("TN09-TW-1122", 600.0, 85.0, ServiceDate(15, 1, 2027), 102.0));
    fleet.push_back(std::make_unique<Car>("TN09-CR-4455", 2200.0, 90.0, ServiceDate(10, 2, 2027), 5, 102.0));
    fleet.push_back(std::make_unique<ElectricCar>("TN09-EV-7788", 2800.0, 95.0, ServiceDate(20, 3, 2027), 5, 60.0, 14.0));
    fleet.push_back(std::make_unique<ElectricBus>("TN09-EB-9900", 8500.0, 92.0, ServiceDate(5, 4, 2027), 42, 240.0, 14.0));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== Initial Fleet ===\n";
    for (const auto& v : fleet) v->printSummary();

    std::cout << "\n=== Renting All Vehicles ===\n";
    for (auto& v : fleet) {
        std::cout << "Rent " << v->getRegNo() << ": " << (v->rentOut() ? "OK" : "Failed") << "\n";
    }

    std::cout << "\n=== Returning Vehicles (with late fees & usage) ===\n";
    double usage[5] = { 0.0, 4.5, 18.0, 45.0, 160.0 };
    int late[5]     = { 1,   0,   1,    2,    1 };
    for (std::size_t i = 0; i < fleet.size(); ++i) {
        double bill = fleet[i]->returnVehicle(3, late[i], usage[i]);
        std::cout << fleet[i]->getRegNo() << " (" << fleet[i]->category()
                  << ") -> 3 days + " << late[i] << " late day(s) -> Bill: Rs. " << bill << "\n";
    }
    return 0;
}
