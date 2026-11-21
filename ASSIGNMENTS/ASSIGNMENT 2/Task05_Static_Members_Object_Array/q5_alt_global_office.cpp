#include <iostream>
#include <string>

class TicketOffice {
    int issuedCount = 0;
    int capacity;
    std::string busLabel;

public:
    TicketOffice(std::string label, int cap) : capacity(cap), busLabel(std::move(label)) {}

    int assignSeat() {
        if (issuedCount < capacity) {
            ++issuedCount;
            return issuedCount;
        }
        return 0;
    }

    int totalIssued() const { return issuedCount; }
    const std::string& label() const { return busLabel; }
};

class ScopedTicket {
    int seat;
    std::string passenger;

public:
    ScopedTicket(TicketOffice& office, std::string name)
        : seat(office.assignSeat()), passenger(std::move(name)) {}

    void print(const TicketOffice& office) const {
        std::cout << "[" << office.label() << "] " << passenger << ": "
                  << (seat ? "Seat " + std::to_string(seat) : "Waiting") << "\n";
    }
};

int main() {
    TicketOffice busA("Bus-A (Morning)", 2);
    TicketOffice busB("Bus-B (Afternoon)", 2);

    ScopedTicket a1(busA, "Meera"), a2(busA, "Karthik"), a3(busA, "Nisha");
    ScopedTicket b1(busB, "Rohan"), b2(busB, "Priya");

    a1.print(busA); a2.print(busA); a3.print(busA);
    b1.print(busB); b2.print(busB);
    std::cout << "Bus-A issued: " << busA.totalIssued()
              << ", Bus-B issued: " << busB.totalIssued() << "\n";
    return 0;
}
