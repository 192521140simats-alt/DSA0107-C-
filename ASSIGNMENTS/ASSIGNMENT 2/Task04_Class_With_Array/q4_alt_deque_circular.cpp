#include <iostream>
#include <deque>
#include <chrono>

class CircularStatement {
private:
    static const int CAP = 10;
    double buf[CAP]{};
    int head = 0;
    int sz = 0;

public:
    void push(double val) {
        if (sz < CAP) {
            buf[(head + sz) % CAP] = val;
            ++sz;
        } else {
            buf[head] = val;
            head = (head + 1) % CAP;
        }
    }
    int size() const { return sz; }
};

class DequeStatement {
private:
    static const int CAP = 10;
    std::deque<double> dq;

public:
    void push(double val) {
        if (static_cast<int>(dq.size()) == CAP) {
            dq.pop_front();
        }
        dq.push_back(val);
    }
    std::size_t size() const { return dq.size(); }
};

int main() {
    const int N = 200000;
    CircularStatement circ;
    DequeStatement deq;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) circ.push(static_cast<double>(i));
    auto t2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) deq.push(static_cast<double>(i));
    auto t3 = std::chrono::high_resolution_clock::now();

    auto usCirc = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    auto usDeq  = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
    std::cout << "200,000 pushes -> Circular buffer: " << usCirc
              << " us | std::deque: " << usDeq << " us"
              << " (sizes: " << circ.size() << ", " << deq.size() << ")\n";
    return 0;
}
