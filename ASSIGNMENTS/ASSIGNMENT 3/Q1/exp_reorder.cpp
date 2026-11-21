#include <iostream>
class ReorderDemo {
    int firstDeclared;
    int secondDeclared;
public:
    ReorderDemo(int val) : secondDeclared(firstDeclared + 10), firstDeclared(val) {}
    void show() const { std::cout << "firstDeclared=" << firstDeclared << ", secondDeclared=" << secondDeclared << '\n'; }
};
int main() { ReorderDemo d(5); d.show(); return 0; }
