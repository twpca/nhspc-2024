#include "testlib.h"
#include <bits/stdc++.h>

const int SUBTASKS = 10;
const int N[] = {-1, 1, 1, 1, 2, 10, 10, 1, 20, 40, 39};
const int M[] = {-1, 1, 2, 3, 2, 10, 10, 1599, 24, 40, 39};

long long sum_ans = 0;
void solve(int subtask) {

    int n = inf.readInt(N[subtask], N[subtask], "n");
    inf.readSpace();
    int m = inf.readInt(M[subtask], M[subtask], "m");
    inf.readEoln();
    ensuref(1 <= n * m && n * m <= 1600, "!(1 <= n * m <= 1600)");

    std::vector<std::vector<int>> a(5 * n, std::vector<int>(5 * m));
    for (int i = 0; i < 5 * n; i++) {
        for (int j = 0; j < 5 * m; j++) {
            a[i][j] = inf.readInt(-1, 0);
            if (j < 5 * m - 1) inf.readSpace();
            else inf.readEoln();
        }
    }
    inf.readEof();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            for (int x = 0; x < 5; x++) {
                for (int y = 0; y < 5; y++) {
                    if (a[i * 5 + x][j * 5 + y] == -1) cnt++;
                }
            }
            ensuref(cnt <= 2, "more than two special cells in a block");
        }
    }

    for (int i = 0; i < 5 * n; i++) {
        for (int j = 0; j < 5 * n; j++) {
            int cnt = a[i][j] == -1;
            if (i + 1 < 5 * n) cnt += a[i + 1][j] == -1;
            if (j + 1 < 5 * m) cnt += a[i][j + 1] == -1;
            if (i + 1 < 5 * n && j + 1 < 5 * m) cnt += a[i + 1][j + 1] == -1;
            ensuref(cnt <= 1, "adjacent special cells");
        }
    }
    
}


int get_subtask(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp("--testcase", argv[i - 1])) {
            int subtask = atoi(argv[i]);
            assert(0 <= subtask && subtask <= SUBTASKS);
            return subtask;
        }
    }
    assert(0);
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int subtask = get_subtask(argc, argv);
    solve(subtask);

    return 0;
}
