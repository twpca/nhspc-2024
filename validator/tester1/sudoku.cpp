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

constexpr long long int N[] = {20, 2, 3, 3, 10, 20, 4, 8, 12, 16, 20};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int n = inf.readInt(N[s], N[s], "n");
    inf.readChar('\n');

    std::vector<std::vector<int>> grid(n * n, std::vector<int>(n * n)); 
    for (int i = 0; i < n * n; ++i)
        for (int j = 0; j < n * n; ++j) {
            grid[i][j] = inf.readInt(0, n * n, "a_" + std::to_string(i) + "," + std::to_string(j));
            if (j + 1 < n * n) inf.readSpace();
            else inf.readEoln();
        }

    // check row
    for (int i = 0; i < n * n; ++i) {
        std::vector<int> vis(n * n + 1);
        for (int j = 0; j < n * n; ++j)
            if (grid[i][j] != 0) {
                ensuref(vis[grid[i][j]] == 0, "row %d not valid", i + 1);
                vis[grid[i][j]] = 1;
            }
    }

    // check column
    for (int i = 0; i < n * n; ++i) {
        std::vector<int> vis(n * n + 1);
        for (int j = 0; j < n * n; ++j)
            if (grid[j][i] != 0) {
                ensuref(vis[grid[j][i]] == 0, "column %d not valid", i + 1);
                vis[grid[j][i]] = 1;
            }
    }

    // check region
    for (int i = 0; i < n * n; ++i) {
        std::vector<int> vis(n * n + 1);
        int sx = i / n * n, sy = (i % n) * n;
        for (int a = 0; a < n; ++a)
            for (int b = 0; b < n; ++b)
                if (grid[sx + a][sy + b] != 0) {
                    ensuref(vis[grid[sx + a][sy + b]] == 0, "region (%d, %d) not valid", i / n + 1, i % n + 1);
                    vis[grid[sx + a][sy + b]] = 1;
                }
    }

    inf.readEof();
    return 0;
}
