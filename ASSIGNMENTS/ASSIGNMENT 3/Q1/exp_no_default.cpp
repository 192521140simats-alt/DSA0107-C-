#include <string>
class BookNoDefault {
    std::string title;
    int copies;
public:
    BookNoDefault(const std::string& t, int c) : title(t), copies(c) {}
};
int main() {
    BookNoDefault shelf[3];
    return 0;
}
