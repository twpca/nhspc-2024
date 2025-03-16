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

constexpr int MIN_M = 2;
constexpr int MAX_M[] = {1'000'000, 1'000, 100'000, 1'000'000};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int m = inf.readInt(MIN_M, MAX_M[s], "m");
    inf.readChar('\n');

    std::vector<std::vector<int>> G(m + 1);
    for (int i = 1; i < m; ++i) {
        int u = inf.readInt(1, m, "u_" + std::to_string(i));
        inf.readSpace();
        int v = inf.readInt(1, m, "v_" + std::to_string(i));
        inf.readChar('\n');
        G[u].push_back(v);
        G[v].push_back(u);
    }
    inf.readEof();

    std::vector<int> vis(m + 1);
    auto dfs = [&](auto _dfs, int u) -> void {
        vis[u] = 1;
        for (int v : G[u])
            if (!vis[v])
                _dfs(_dfs, v);
    };

    dfs(dfs, 1);
    ensuref(accumulate(vis.begin(), vis.end(), 0) == m, "not a valid tree");

    return 0;
}
