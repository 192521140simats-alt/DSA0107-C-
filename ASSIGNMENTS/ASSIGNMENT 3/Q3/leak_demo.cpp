class LeakDemo {
    char** grid; int r;
public:
    LeakDemo(int rows, int cols) : r(rows) {
        grid = new char*[r];
        for (int i = 0; i < r; ++i) grid[i] = new char[cols];
    }
};
int main() { LeakDemo* d = new LeakDemo(5, 5); (void)d; return 0; }
