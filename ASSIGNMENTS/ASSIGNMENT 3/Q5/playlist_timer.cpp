#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <chrono>

class Time {
    int totalSeconds;
public:
    Time(int h = 0, int m = 0, int s = 0) : totalSeconds(h * 3600 + m * 60 + s) {}
    Time& operator++() { ++totalSeconds; return *this; }
    Time operator++(int) { Time old = *this; ++totalSeconds; return old; }
    bool operator==(const Time& rhs) const { return totalSeconds == rhs.totalSeconds; }
    bool operator<(const Time& rhs) const  { return totalSeconds < rhs.totalSeconds; }
    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        int h = t.totalSeconds / 3600;
        int m = (t.totalSeconds % 3600) / 60;
        int s = t.totalSeconds % 60;
        os << h << ':' << std::setw(2) << std::setfill('0') << m
           << ':' << std::setw(2) << std::setfill('0') << s;
        return os;
    }
};

class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> list) : tracks(list) {}
    int size() const { return static_cast<int>(tracks.size()); }
    std::string& operator[](int i) {
        if (i < 0 || i >= size()) throw std::out_of_range("Playlist index out of bounds: " + std::to_string(i));
        return tracks[i];
    }
    const std::string& operator[](int i) const {
        if (i < 0 || i >= size()) throw std::out_of_range("Playlist index out of bounds: " + std::to_string(i));
        return tracks[i];
    }
    const std::string& uncheckedAt(int i) const { return tracks[i]; }
};

int main() {
    std::cout << "=== Q5: Music Playlist and Track Timer ===\n\n";
    Time t(0, 59, 59);
    std::cout << "Initial Time : " << t << '\n';
    Time a = t++;
    std::cout << "After a = t++ (rollover check): a = " << a << ", t = " << t << '\n';
    Time b = ++t;
    std::cout << "After b = ++t                 : b = " << b << ", t = " << t << '\n';
    std::cout << "Comparison (a < b): " << std::boolalpha << (a < b)
              << " | (b == t): " << (b == t) << "\n\n";

    Playlist pl{"Track 1 - Overture", "Track 2 - Nocturne", "Track 3 - Coda"};
    pl[1] = "Track 2 - Nocturne (Remastered)";
    const Playlist& cpl = pl;
    for (int i = 0; i < cpl.size(); ++i) std::cout << "pl[" << i << "] = " << cpl[i] << '\n';

    std::cout << "\n--- Out-of-Range Subscript Tests ---\n";
    for (int bad : {-1, pl.size()}) {
        try { std::cout << pl[bad] << '\n'; }
        catch (const std::out_of_range& e) {
            std::cout << "Caught Exception for pl[" << bad << "]: " << e.what() << '\n';
        }
    }

    Time benchT(0, 0, 0);
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i) ++benchT;
    auto t2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i) benchT++;
    auto t3 = std::chrono::high_resolution_clock::now();

    volatile size_t sink = 0;
    auto t4 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i) sink += cpl[i % 3].size();
    auto t5 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000000; ++i) sink += cpl.uncheckedAt(i % 3).size();
    auto t6 = std::chrono::high_resolution_clock::now();
    (void)sink;

    std::cout << "\n--- Timing Measurements (10,000,000 iterations) ---\n";
    std::cout << "Prefix ++t               : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";
    std::cout << "Postfix t++              : " << std::chrono::duration<double, std::milli>(t3 - t2).count() << " ms\n";
    std::cout << "Checked operator[]       : " << std::chrono::duration<double, std::milli>(t5 - t4).count() << " ms\n";
    std::cout << "Unchecked array access   : " << std::chrono::duration<double, std::milli>(t6 - t5).count() << " ms\n";
    return 0;
}
