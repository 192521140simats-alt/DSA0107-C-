#include <iostream>
#include <string>
class ShallowPrescription {
    int n;
    std::string* medicines;
public:
    explicit ShallowPrescription(int count) : n(count), medicines(new std::string[count]) {}
    ~ShallowPrescription() { delete[] medicines; }
    void set(int i, const std::string& m) { medicines[i] = m; }
    std::string get(int i) const { return medicines[i]; }
};
int main() {
    ShallowPrescription p(2);
    p.set(0, "Paracetamol"); p.set(1, "ORS");
    ShallowPrescription q = p;
    q.set(1, "Cetirizine");
    std::cout << "Original p[1] corrupted to: " << p.get(1) << '\n';
    return 0;
}
