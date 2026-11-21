#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

static int copy_count = 0;
class TrackedPrescription {
    int n;
    std::string* medicines;
public:
    explicit TrackedPrescription(int count) : n(count), medicines(new std::string[count]) {
        for (int i = 0; i < n; ++i) medicines[i] = "Med_" + std::to_string(i);
    }
    TrackedPrescription(const TrackedPrescription& other)
        : n(other.n), medicines(new std::string[other.n]) {
        ++copy_count;
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
    }
    TrackedPrescription& operator=(const TrackedPrescription& other) {
        if (this == &other) {
            std::cout << "[Self-Assignment Guard] Detected p = p; skipped reallocation safely.\n";
            return *this;
        }
        std::string* temp = new std::string[other.n];
        for (int i = 0; i < other.n; ++i) temp[i] = other.medicines[i];
        delete[] medicines;
        n = other.n;
        medicines = temp;
        return *this;
    }
    ~TrackedPrescription() { delete[] medicines; }
    std::string get(int i) const { return medicines[i]; }
};

void passByValue(TrackedPrescription tp) { (void)tp; }
void passByConstRef(const TrackedPrescription& tp) { (void)tp; }

int main() {
    std::cout << "=== Q2 Experimental Investigation ===\n\n";
    TrackedPrescription p(5);
    copy_count = 0; passByValue(p);
    std::cout << "Copies made when passed by VALUE: " << copy_count << '\n';
    copy_count = 0; passByConstRef(p);
    std::cout << "Copies made when passed by CONST REFERENCE: " << copy_count << '\n';
    p = p;
    std::cout << "After self-assignment, p[0] = " << p.get(0) << '\n';

    std::cout << "\n--- Copy Performance Benchmark (Raw Dynamic Array vs std::vector) ---\n";
    std::cout << std::left << std::setw(15) << "Medicines (n)"
              << std::setw(25) << "Raw Deep Copy (us)"
              << std::setw(25) << "std::vector Copy (us)" << '\n';
    for (int sz : {10, 1000, 100000}) {
        TrackedPrescription rawSrc(sz);
        auto t1 = std::chrono::high_resolution_clock::now();
        TrackedPrescription rawDst = rawSrc;
        auto t2 = std::chrono::high_resolution_clock::now();
        double raw_us = std::chrono::duration<double, std::micro>(t2 - t1).count();
        (void)rawDst;

        std::vector<std::string> vecSrc(sz, "Med_0");
        auto t3 = std::chrono::high_resolution_clock::now();
        std::vector<std::string> vecDst = vecSrc;
        auto t4 = std::chrono::high_resolution_clock::now();
        double vec_us = std::chrono::duration<double, std::micro>(t4 - t3).count();
        (void)vecDst;

        std::cout << std::left << std::setw(15) << sz
                  << std::setw(25) << std::fixed << std::setprecision(2) << raw_us
                  << std::setw(25) << vec_us << '\n';
    }
    return 0;
}
