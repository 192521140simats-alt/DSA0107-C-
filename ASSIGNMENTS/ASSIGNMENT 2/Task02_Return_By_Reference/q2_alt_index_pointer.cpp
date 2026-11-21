#include <iostream>
#include <vector>

int highestMarkIndex(const std::vector<int>& v) {
    int idx = 0;
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] > v[idx]) idx = static_cast<int>(i);
    }
    return idx;
}

int* highestMarkPointer(std::vector<int>& v) {
    if (v.empty()) return nullptr;
    std::size_t idx = 0;
    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] > v[idx]) idx = i;
    }
    return &v[idx];
}

int main() {
    std::vector<int> marks = {64, 91, 83, 77};
    int idx = highestMarkIndex(marks);
    marks[idx] += 2;
    std::cout << "Index-based update -> marks[" << idx << "] = " << marks[idx] << "\n";

    int* ptr = highestMarkPointer(marks);
    if (ptr) {
        *ptr += 1;
        std::cout << "Pointer-based update -> *ptr = " << *ptr << "\n";
    }
    return 0;
}
