#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>

int subtask(int argc, char **argv) {
   for (int i = 0; i + 1 < argc; i++) {
      if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

constexpr int N[] = {1, 1, 1, 1, 2, 10, 10, 1, 20, 40, 39};
constexpr int M[] = {1, 1, 2, 3, 2, 10, 10, 1599, 24, 40, 39};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int n = inf.readInt(N[s], N[s], "n");
    inf.readSpace();
    int m = inf.readInt(M[s], M[s], "m");
    inf.readChar('\n');

    std::vector<std::vector<int>> grid(5 * n, std::vector<int>(5 * m)); 
    for (int i = 0; i < 5 * n; ++i)
        for (int j = 0; j < 5 * m; ++j) {
            grid[i][j] = inf.readInt(-1, 0, "a_" + std::to_string(i) + "," + std::to_string(j));
            if (j + 1 < 5 * m) inf.readSpace();
            else inf.readEoln();
        }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int sum = 0;
            for (int a = 0; a < 5; ++a)
                for (int b = 0; b < 5; ++b)
                    sum += grid[i * 5 + a][j * 5 + b];
            ensuref(sum >= -2, "more than three -1 in a region");
        }
    
    for (int i = 0; i + 1 < 5 * n; ++i)
        for (int j = 0; j + 1 < 5 * m; ++j) {
            ensuref(grid[i][j] + grid[i + 1][j] + grid[i][j + 1] + grid[i + 1][j + 1] >= -1, "more than three -1 in a 2x2 block");
        }

    inf.readEof();
    return 0;
}
