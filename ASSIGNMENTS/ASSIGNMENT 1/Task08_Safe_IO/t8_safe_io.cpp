#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

bool readIntSafe(const std::string& prompt, int& outVal) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> outVal) {
            return true;
        }
        if (std::cin.eof()) {
            return false;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid numeric input. Please enter an integer.\n";
    }
}

int main() {
    // Feed simulated operator session including invalid letters 'abc' before valid hour 9
    std::istringstream simulated("abc\n9\n3\n");
    auto* origBuf = std::cin.rdbuf(simulated.rdbuf());

    int hour = -1;
    int zone = -1;
    if (readIntSafe("Enter hour (0-23): ", hour) && readIntSafe("Enter zone (1-3): ", zone)) {
        long long farePaise = 3600;
        std::cout << "\n=== Metro Gate Journey Report ===\n";
        std::cout << std::left << std::setw(12) << "Hour"
                  << std::setw(10) << "Zone"
                  << std::right << std::setw(14) << "Fare (Rs.)" << "\n";
        std::cout << std::string(36, '-') << "\n";
        std::cout << std::left << std::setw(12) << hour
                  << std::setw(10) << zone
                  << std::right << std::setw(14) << std::fixed << std::setprecision(2)
                  << (farePaise / 100.0) << "\n";
    }

    std::cin.rdbuf(origBuf);
    return 0;
}
