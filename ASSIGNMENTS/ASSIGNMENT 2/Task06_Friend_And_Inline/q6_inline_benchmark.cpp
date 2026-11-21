#include <iostream>
#include <cstdlib>
#include <chrono>

class TimeFriendInline {
    int h, m;
public:
    TimeFriendInline(int hh, int mm) : h(hh), m(mm) {}
    friend inline int diffInline(const TimeFriendInline& a, const TimeFriendInline& b) {
        return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m));
    }
};

class TimeFriendNoInline {
    int h, m;
public:
    TimeFriendNoInline(int hh, int mm) : h(hh), m(mm) {}
    friend int diffNoInline(const TimeFriendNoInline& a, const TimeFriendNoInline& b);
};

int diffNoInline(const TimeFriendNoInline& a, const TimeFriendNoInline& b) {
    return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m));
}

class TimeMemberGetter {
    int h, m;
public:
    TimeMemberGetter(int hh, int mm) : h(hh), m(mm) {}
    int getH() const { return h; }
    int getM() const { return m; }
    int minutesTo(const TimeMemberGetter& other) const {
        return std::abs((h * 60 + m) - (other.h * 60 + other.m));
    }
};

int main() {
    const int ITERS = 10000000;
    volatile int sink = 0;

    TimeFriendInline fi1(8, 20), fi2(15, 45);
    auto s1 = std::chrono::high_resolution_clock::now();
    int acc1 = 0;
    for (int i = 0; i < ITERS; ++i) acc1 += diffInline(fi1, fi2);
    auto e1 = std::chrono::high_resolution_clock::now();
    sink = acc1;

    TimeFriendNoInline fn1(8, 20), fn2(15, 45);
    auto s2 = std::chrono::high_resolution_clock::now();
    int acc2 = 0;
    for (int i = 0; i < ITERS; ++i) acc2 += diffNoInline(fn1, fn2);
    auto e2 = std::chrono::high_resolution_clock::now();
    sink = acc2;

    TimeMemberGetter mg1(8, 20), mg2(15, 45);
    auto s3 = std::chrono::high_resolution_clock::now();
    int acc3 = 0;
    for (int i = 0; i < ITERS; ++i) acc3 += mg1.minutesTo(mg2);
    auto e3 = std::chrono::high_resolution_clock::now();
    sink = acc3;

    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(e1 - s1).count();
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(e2 - s2).count();
    auto ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(e3 - s3).count();

    std::cout << "10,000,000 calls -> inline friend: " << ms1
              << " ms | non-inline friend: " << ms2
              << " ms | member fn: " << ms3 << " ms (sink=" << sink << ")\n";
    return 0;
}
