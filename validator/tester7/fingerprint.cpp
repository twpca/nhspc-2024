#include <iostream>
#include <vector>
#include <queue>

#include "../../generator/testlib.h"

int subtask(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp("--testcase", argv[i - 1])) {
            return atoi(argv[i]);
        }
    }
    exit(0);
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = subtask(argc, argv);
    int n = inf.readInt(2, 1000000);
    inf.readChar('\n');
    int t = n;
    std::vector<std::vector<int>> v(n + 1);

    std::vector<int> cnt(t + 1);
    for (int i = 0; i < t - 1; i++) {
        int x, y;
        x = inf.readInt(1, t);
        inf.readSpace();
        y = inf.readInt(1, t);
        inf.readChar('\n');
        v[x].emplace_back(y);
        v[y].emplace_back(x);
        cnt[x] += 1;
        cnt[y] += 1;
    }
    if (c == 1) {
        ensuref(n <= 1000 && n >= 2, "for subtask 1 n must <= 1000");
    }
    if (c == 2) {
        for (int i = 1; i <= n; i++) {
            ensuref(cnt[i] == 1 || cnt[i] == 3, "degree of external node must be 1 and degree of internal node must be 3");
        }
    }

    std::queue<int> bfs;
    bfs.emplace(1);
    std::vector<bool> vis(n + 1);
    std::vector<int> pre(n + 1);
    while(bfs.size() > 0) {
        int cur = bfs.front();
        bfs.pop();
        for (int i : v[cur]) {
            if (i == pre[cur])
                continue;
            ensuref (vis[i] == 0, "cycle detected");
            vis[i] = 1;
            pre[i] = cur;
            bfs.emplace(i);
        }
    }

    inf.readEof();
}

