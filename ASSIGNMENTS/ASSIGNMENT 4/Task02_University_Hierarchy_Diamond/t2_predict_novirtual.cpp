#include <iostream>

struct Person  { std::string name = "Tharika"; Person()  { std::cout << "Person "; } };
struct Student : Person { Student() { std::cout << "Student "; } };
struct Staff   : Person { Staff()   { std::cout << "Staff "; } };
struct TeachingAssistant : Student, Staff {
    TeachingAssistant() { std::cout << "TA "; }
};

int main()
{
    TeachingAssistant ta;
    std::cout << '\n';
    // Uncommenting next line causes: error: request for member 'name' is ambiguous
    // std::cout << ta.name << '\n';
    std::cout << "Disambiguated: " << ta.Student::name << " / " << ta.Staff::name << '\n';
    return 0;
}
