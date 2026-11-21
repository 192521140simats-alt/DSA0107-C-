#include <iostream>
#include <string>

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    std::string name;

public:
    explicit BusTicket(const std::string& n) : seat(0), name(n)
    {
        if (issued < CAPACITY) {
            ++issued;
            seat = issued;
        }
    }

    static int count()
    {
        return issued;
    }

    void print() const
    {
        std::cout << name << ": "
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting"))
                  << '\n';
    }
};

int BusTicket::issued = 0;

void runTripBatch(int batchNo) {
    std::cout << "--- Function call #" << batchNo << " ---\n";
    BusTicket t1("BatchUserA");
    BusTicket t2("BatchUserB");
    t1.print();
    t2.print();
    std::cout << "Issued after batch #" << batchNo << ": " << BusTicket::count() << "\n";
}

int main()
{
    BusTicket trip[4] = {
        BusTicket("Asha"), BusTicket("Bala"),
        BusTicket("Chitra"), BusTicket("Dev")
    };
    for (const BusTicket& t : trip) t.print();
    std::cout << "Issued: " << BusTicket::count() << '\n';

    runTripBatch(1);
    runTripBatch(2);
    return 0;
}
