#include <iostream>
#include <cstdlib>

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b)
{
    int minsA = a.h * 60 + a.m;
    int minsB = b.h * 60 + b.m;
    return std::abs(minsA - minsB);
}

bool earlier(const Time& a, const Time& b)
{
    return (a.h * 60 + a.m) < (b.h * 60 + b.m);
}

int main()
{
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    Time tSame1(11, 30), tSame2(11, 30);
    std::cout << "Same time (11:30, 11:30) -> diff=" << minutesBetween(tSame1, tSame2)
              << ", earlier=" << earlier(tSame1, tSame2) << '\n';

    Time morning(8, 15), afternoon(14, 5);
    std::cout << "Across noon (08:15, 14:05) -> diff=" << minutesBetween(morning, afternoon)
              << ", earlier(morning, afternoon)=" << earlier(morning, afternoon)
              << ", earlier(afternoon, morning)=" << earlier(afternoon, morning) << '\n';
    return 0;
}
