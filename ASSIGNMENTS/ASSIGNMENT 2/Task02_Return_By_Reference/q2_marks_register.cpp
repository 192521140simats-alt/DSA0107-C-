#include <iostream>

int& highestMarkRef(int marks[], int n) {
    int bestIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[bestIdx]) {
            bestIdx = i;
        }
    }
    return marks[bestIdx];
}

const int& highestMarkConstRef(const int marks[], int n) {
    int bestIdx = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[bestIdx]) {
            bestIdx = i;
        }
    }
    return marks[bestIdx];
}

int highestMarkCopy(const int marks[], int n) {
    int best = marks[0];
    for (int i = 1; i < n; ++i) {
        if (marks[i] > best) {
            best = marks[i];
        }
    }
    return best;
}

int main() {
    int marks[5] = {78, 92, 85, 88, 92};
    std::cout << "Original marks: ";
    for (int i = 0; i < 5; ++i) std::cout << marks[i] << ' ';
    std::cout << "\n";

    highestMarkRef(marks, 5) += 2;
    std::cout << "After highestMarkRef += 2: ";
    for (int i = 0; i < 5; ++i) std::cout << marks[i] << ' ';
    std::cout << "\n";

    highestMarkRef(marks, 5) = 99;
    std::cout << "After highestMarkRef() = 99: ";
    for (int i = 0; i < 5; ++i) std::cout << marks[i] << ' ';
    std::cout << "\n";

    const int& topReadOnly = highestMarkConstRef(marks, 5);
    int topValCopy = highestMarkCopy(marks, 5);
    std::cout << "const int& top: " << topReadOnly << ", copy top: " << topValCopy << "\n";
    return 0;
}
