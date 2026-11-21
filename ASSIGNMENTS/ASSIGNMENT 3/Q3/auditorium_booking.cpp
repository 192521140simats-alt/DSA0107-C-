#include <iostream>
#include <string>
#include <iomanip>

class AuditoriumEvent {
private:
    std::string eventName;
    int rows;
    int seatsPerRow;
    char** seatMap;
    int bookedCount;

public:
    AuditoriumEvent(const std::string& name, int r, int c)
        : eventName(name), rows(r), seatsPerRow(c), seatMap(nullptr), bookedCount(0) {
        std::cout << "[Ctor] Creating event \"" << eventName << "\" (" << rows << "x" << seatsPerRow << ")\n";
        if (rows > 0 && seatsPerRow > 0) {
            seatMap = new char*[rows];
            for (int i = 0; i < rows; ++i) {
                seatMap[i] = new char[seatsPerRow];
                for (int j = 0; j < seatsPerRow; ++j) seatMap[i][j] = 'O';
            }
        }
    }

    ~AuditoriumEvent() {
        int total = (rows > 0 && seatsPerRow > 0) ? (rows * seatsPerRow) : 0;
        std::cout << "[Dtor] Closing event \"" << eventName << "\" | Booked: "
                  << bookedCount << "/" << total << " seats | Memory released.\n";
        if (seatMap != nullptr) {
            for (int i = 0; i < rows; ++i) delete[] seatMap[i];
            delete[] seatMap;
        }
    }

    AuditoriumEvent(const AuditoriumEvent&) = delete;
    AuditoriumEvent& operator=(const AuditoriumEvent&) = delete;

    bool bookSeat(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow || !seatMap || seatMap[r][s] == 'B') return false;
        seatMap[r][s] = 'B'; ++bookedCount; return true;
    }

    bool cancelSeat(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow || !seatMap || seatMap[r][s] == 'O') return false;
        seatMap[r][s] = 'O'; --bookedCount; return true;
    }

    void printMap() const {
        std::cout << "Seat Map for \"" << eventName << "\":\n";
        if (rows == 0 || seatsPerRow == 0) {
            std::cout << "  (Empty Auditorium: 0 rows)\n";
            return;
        }
        for (int i = 0; i < rows; ++i) {
            std::cout << "  Row " << i << ": ";
            for (int j = 0; j < seatsPerRow; ++j) std::cout << seatMap[i][j] << ' ';
            std::cout << '\n';
        }
    }
};

int main() {
    std::cout << "=== Q3: Auditorium Seat Booking (Dynamic Constructors & Destructors) ===\n\n";
    AuditoriumEvent mainShow("Symphony Night (Stack)", 3, 4);
    mainShow.bookSeat(0, 1); mainShow.bookSeat(1, 2); mainShow.bookSeat(2, 3);
    mainShow.cancelSeat(1, 2);
    mainShow.printMap();

    std::cout << "\n--- Entering Inner Block Scope ---\n";
    {
        AuditoriumEvent workshop("AI Workshop (Block)", 2, 3);
        workshop.bookSeat(0, 0); workshop.bookSeat(1, 1);
        std::cout << "--- Exiting Inner Block Scope ---\n";
    }

    std::cout << "\n--- Allocating Event on Heap ---\n";
    AuditoriumEvent* gala = new AuditoriumEvent("Annual Gala (Heap)", 2, 2);
    gala->bookSeat(0, 1);
    delete gala;

    std::cout << "\n--- Zero-Rows Edge Case ---\n";
    AuditoriumEvent emptyHall("Virtual Stream (0 Rows)", 0, 10);
    emptyHall.printMap();
    std::cout << "Booking attempt on 0-row hall: " << std::boolalpha << emptyHall.bookSeat(0, 0) << '\n';

    std::cout << "\n--- Memory Footprint Measurement (Jagged char** vs Contiguous 1D Block) ---\n";
    std::cout << std::left << std::setw(15) << "Dimensions"
              << std::setw(22) << "2D char** Bytes"
              << std::setw(22) << "1D Flat Block Bytes"
              << std::setw(18) << "Pointer Overhead" << '\n';
    for (auto [r, c] : {std::pair{10, 20}, std::pair{100, 200}, std::pair{1000, 2000}}) {
        size_t ptr_overhead = static_cast<size_t>(r) * sizeof(char*);
        size_t flat_bytes = static_cast<size_t>(r) * static_cast<size_t>(c) * sizeof(char);
        std::string dim = std::to_string(r) + "x" + std::to_string(c);
        std::cout << std::left << std::setw(15) << dim
                  << std::setw(22) << (ptr_overhead + flat_bytes)
                  << std::setw(22) << flat_bytes
                  << std::setw(18) << ptr_overhead << '\n';
    }
    std::cout << "\n--- End of main() (Stack destructors run in LIFO order) ---\n";
    return 0;
}
