#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>
#include <vector>
#include <numeric>

int subtask(int argc, char **argv) {
   for (int i = 0; i + 1 < argc; i++) {
      if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

constexpr int MIN_N = 1;
constexpr int MAX_N[] = {10'000, 500, 5'000, 10'000, 10'000};
constexpr int MIN_M = 1;
constexpr int MAX_M[] = {100'000, 100'000, 10'000, 100'000, 100'000};
constexpr int MIN_Q = 1;
constexpr int MAX_Q = 30'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readSpace();
    int m = inf.readInt(MIN_M, MAX_M[s], "m");
    inf.readSpace();
    int q = inf.readInt(MIN_Q, MAX_Q, "q");
    inf.readChar('\n');

    std::vector<std::set<int>> G(n + 1);
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x_" + std::to_string(i));
        inf.readSpace();
        int y = inf.readInt(1, n, "y_" + std::to_string(i));
        inf.readChar('\n');
        ensuref(x != y, "self loop");
        ensuref(G[x].insert(y).second, "multiple edges");
        ensuref(G[y].insert(x).second, "multiple edges");
    }

    for (int i = 1; i <= q; ++i) {
        inf.readInt(1, n, "s_" + std::to_string(i));
        inf.readSpace();
        inf.readInt(1, n, "t_" + std::to_string(i));
        inf.readChar('\n');
    }

    inf.readEof();

    std::vector<int> vis(n + 1);
    auto dfs = [&](auto _dfs, int u) -> void {
        vis[u] = 1;
        for (int v : G[u])
            if (!vis[v])
                _dfs(_dfs, v);
    };

    dfs(dfs, 1);
    ensuref(accumulate(vis.begin(), vis.end(), 0) == n, "not connected");

    return 0;
}
