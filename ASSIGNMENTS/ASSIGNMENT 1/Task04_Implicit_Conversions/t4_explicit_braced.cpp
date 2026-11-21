#include <iostream>

int main()
{
    int a{7}, b{2};
    double c{static_cast<double>(a) / static_cast<double>(b)};
    double d{static_cast<double>(a) / static_cast<double>(b)};
    std::cout << c << ' ' << d << '\n';

    char ch{static_cast<char>('A' + 2)};
    std::cout << ch << ' ' << (static_cast<int>(ch) + 1) << '\n';

    bool flag{true};
    std::cout << static_cast<int>(flag) << ' ' << std::boolalpha << flag << '\n';

    unsigned int u{1U};
    int s{-1};
    bool lessThan{(s < 0) ? true : (static_cast<unsigned int>(s) < u)};
    std::cout << (lessThan ? "s < u" : "s >= u") << '\n';
    return 0;
}
