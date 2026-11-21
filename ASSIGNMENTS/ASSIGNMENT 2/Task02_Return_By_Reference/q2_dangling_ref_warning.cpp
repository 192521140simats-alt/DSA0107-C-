#include <iostream>
#include <vector>

int& danglingLocalRef() {
    int tempScore = 95;
    return tempScore; // WARNING: reference to local variable 'tempScore' returned
}

int main() {
    int& badRef = danglingLocalRef();
    std::cout << "Dangling local ref read (UB): " << badRef << "\n";

    std::vector<int> reg = {70, 80, 90};
    int& elementRef = reg[2];
    std::cout << "Before growth: reg[2] = " << elementRef
              << ", cap = " << reg.capacity() << "\n";

    for (int i = 0; i < 20; ++i) {
        reg.push_back(75 + i);
    }
    std::cout << "After growth : new cap = " << reg.capacity()
              << " (old reference elementRef may point to freed heap memory)\n";
    return 0;
}
