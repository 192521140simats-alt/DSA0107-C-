#include <iostream>
#include <string>
#include <stdexcept>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    int copies;

public:
    Book(const std::string& t, const std::string& a, const std::string& i, int c)
        : title(t), author(a), isbn(i), copies(c) {
        if (copies < 0) {
            throw std::invalid_argument("Invalid number of copies: cannot be negative (" + std::to_string(c) + ")");
        }
    }

    explicit Book(const std::string& t)
        : Book(t, "Unknown Donor", "UNASSIGNED", 1) {}

    Book()
        : Book("Untitled Record", "Pending", "N/A", 0) {}

    void setDetails(const std::string& t, const std::string& a, const std::string& i, int c) {
        if (c < 0) throw std::invalid_argument("Invalid number of copies: cannot be negative");
        title = t; author = a; isbn = i; copies = c;
    }

    void print(const std::string& label) const {
        std::cout << "[" << label << "] Title: \"" << title
                  << "\" | Author: " << author
                  << " | ISBN: " << isbn
                  << " | Copies: " << copies << '\n';
    }
};

void catalogBook(Book b) { b.print("Cataloged"); }

int main() {
    std::cout << "=== Q1: Library Book Records (Constructors & Delegation) ===\n\n";
    Book b1;
    b1.print("Default Constructor");

    Book b2("The C++ Programming Language");
    b2.print("Donated Book (1-arg)");

    Book b3("Clean Code", "Robert C. Martin", "978-0132350884", 5);
    b3.print("Full Parameterized");

    Book shelf[2];
    shelf[0].setDetails("Design Patterns", "GoF", "978-0201633610", 3);
    shelf[1].setDetails("Effective Modern C++", "Scott Meyers", "978-1491903995", 4);
    std::cout << "\n--- Array of Books ---\n";
    shelf[0].print("Shelf[0]");
    shelf[1].print("Shelf[1]");

    std::cout << "\n--- Explicit Constructor Test ---\n";
    catalogBook(Book("Refactoring"));
    std::cout << "Explicit call catalogBook(Book(\"Refactoring\")) succeeded; implicit conversion blocked.\n";

    std::cout << "\n--- Negative Copies Validation Test ---\n";
    try {
        Book badBook("Corrupted Record", "Unknown", "000-0000000000", -3);
        badBook.print("Should Not Print");
    } catch (const std::invalid_argument& ex) {
        std::cout << "Caught Exception: " << ex.what() << '\n';
    }
    return 0;
}
