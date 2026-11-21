#include <iostream>
#include <cstring>
#include <string>
#include <chrono>

static int text_copy_count = 0;

class Text {
    char* data;
    size_t len;

public:
    Text(const char* s = "") {
        len = s ? std::strlen(s) : 0;
        data = new char[len + 1];
        if (s) std::memcpy(data, s, len + 1);
        else data[0] = '\0';
    }

    Text(const Text& other) : data(new char[other.len + 1]), len(other.len) {
        ++text_copy_count;
        std::memcpy(data, other.data, len + 1);
    }

    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        char* buf = new char[other.len + 1];
        std::memcpy(buf, other.data, other.len + 1);
        delete[] data;
        data = buf;
        len = other.len;
        return *this;
    }

    ~Text() { delete[] data; }

    Text operator+(const Text& rhs) const {
        Text res;
        delete[] res.data;
        res.len = len + rhs.len;
        res.data = new char[res.len + 1];
        std::memcpy(res.data, data, len);
        std::memcpy(res.data + len, rhs.data, rhs.len + 1);
        return res;
    }

    bool operator==(const Text& rhs) const {
        return len == rhs.len && std::strcmp(data, rhs.data) == 0;
    }

    bool operator!=(const Text& rhs) const { return !(*this == rhs); }
    size_t size() const { return len; }

    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        return os << t.data;
    }
};

int main() {
    std::cout << "=== Q6: SMS Gateway Text Class ===\n\n";
    Text empty("");
    std::string longStr(500, 'X');
    Text longMsg(longStr.c_str());
    std::cout << "Empty message length: " << empty.size() << " | empty == Text(\"\"): " << std::boolalpha << (empty == Text("")) << '\n';
    std::cout << "Long SMS message length: " << longMsg.size() << '\n';

    Text a("Hello, "), b("Tharika"), c("! SMS Gateway Ready.");
    a = a;
    std::cout << "After self-assignment (a = a): \"" << a << "\"\n";

    text_copy_count = 0;
    Text combined = a + b + c;
    std::cout << "Combined SMS: " << combined << '\n';
    std::cout << "Copy constructor invocations in (a + b + c): " << text_copy_count << " (C++17 guaranteed copy elision)\n";
    std::cout << "Comparison (a != b): " << (a != b) << "\n\n";

    const int N = 20000;
    auto t1 = std::chrono::high_resolution_clock::now();
    Text tAcc(""); Text tChunk("A");
    for (int i = 0; i < N; ++i) tAcc = tAcc + tChunk;
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    std::string sAcc(""); std::string sChunk("A");
    for (int i = 0; i < N; ++i) sAcc = sAcc + sChunk;
    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout << "--- 20,000 Concatenations Benchmark (scaled O(N^2) test) ---\n";
    std::cout << "Custom Text class : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms (final len=" << tAcc.size() << ")\n";
    std::cout << "std::string       : " << std::chrono::duration<double, std::milli>(t4 - t3).count() << " ms (final len=" << sAcc.size() << ")\n";
    return 0;
}
