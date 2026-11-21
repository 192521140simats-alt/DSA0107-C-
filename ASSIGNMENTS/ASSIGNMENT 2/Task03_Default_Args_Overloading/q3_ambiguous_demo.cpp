double charge(double weight) { return 40.0 + weight * 15.0; }
double charge(double weight, bool express) { return (express ? 60.0 : 0.0) + 40.0 + weight * 15.0; }
double charge(double weight, bool express = false, bool insured = false) {
    return (express ? 60.0 : 0.0) + (insured ? 35.0 : 0.0) + 40.0 + weight * 15.0;
}

int main() {
    return static_cast<int>(charge(2.5));
}
