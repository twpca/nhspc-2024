#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <numeric>
#include <cmath>
#include <iostream>

void exit_par(double par, const char *msg) {
    printf("%lf\n", par);
    quitp(par, "%s, score = %.9lf", msg, par);
}

int main(int argc, char * argv[]) {
    inf.maxFileSize = 128 * 1024 * 1024; // 128MB
    ouf.maxFileSize = 16 * 1024 * 1024; // 16MB
    ans.maxFileSize = 16 * 1024 * 1024; // 16MB
    setName("special judge for cover");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(), m = inf.readInt();

    std::vector<std::vector<int>> req(n * 5, std::vector<int>(m * 5));
    for (int i = 0; i < n * 5; ++i)
        for (int j = 0; j < m * 5; ++j)
            req[i][j] = inf.readInt();
    
    std::vector<std::vector<std::pair<int, int>>> bricks;
    bricks.push_back({{0, 0}, {0, 1}, {1, 0}});
    bricks.push_back({{0, 0}, {0, 1}, {1, 1}});
    bricks.push_back({{0, 0}, {1, 0}, {1, 1}});
    bricks.push_back({{0, 0}, {1, 0}, {1, -1}});
    bricks.push_back({{0, 0}, {0, 1}, {0, 2}, {0, 3}});
    bricks.push_back({{0, 0}, {1, 0}, {2, 0}, {3, 0}});
    for (auto &v : bricks)
        std::sort(v.begin(), v.end());

    auto check_grid = [&](auto &stream) {
        std::vector<std::vector<int>> grid(n * 5, std::vector<int>(m * 5));
        std::vector<std::vector<std::pair<int, int>>> bucket(15001);
        std::vector<std::vector<int>> table(n * m, std::vector<int>(n * m));
        for (int i = 0; i < n * 5; ++i)
            for (int j = 0; j < m * 5; ++j) {
                grid[i][j] = stream.readInt(-1, 15000, "grid_" + std::to_string(i) + "," + std::to_string(j));
                if (grid[i][j] == 0)
                    quitf(_wa, "Does not fully covered");
                if (req[i][j] == -1 && grid[i][j] != -1)
                    quitf(_wa, "Covered a special cell");
                if (grid[i][j] == -1 && req[i][j] != -1)
                    quitf(_wa, "Generated a new special cell");
                if (grid[i][j] == -1) continue;
                bucket[grid[i][j]].emplace_back(i, j);
            }
        std::vector<std::vector<int>> vis(n, std::vector<int>(m));
        int vis_cnt = 0;
        for (int i = 0; i < 15001; ++i) {
            if (bucket[i].empty()) continue;
            if (bucket[i].size() < 3 || bucket[i].size() > 4)
                quitf(_wa, "not a valid brick: color %d", i);
            auto [mx, my] = *std::min_element(bucket[i].begin(), bucket[i].end());
            for (auto &[x, y] : bucket[i])
                x -= mx, y -= my;
            std::sort(bucket[i].begin(), bucket[i].end());
            if (std::find(bricks.begin(), bricks.end(), bucket[i]) == bricks.end())
                quitf(_wa, "not a valid brick: color %d", i);
            ++vis_cnt;
            std::vector<int> touch;
            for (auto [x, y] : bucket[i]) {
                x += mx, y += my;
                if (vis[x / 5][y / 5] != vis_cnt) {
                    touch.push_back(x / 5 * m + y / 5);
                    vis[x / 5][y / 5] = vis_cnt;
                }
            }
            for (int j : touch)
                for (int k : touch)
                    table[j][k] = 1;
        }
        int res = 0;
        for (int i = 0; i < n * m; ++i)
            for (int j = i + 1; j < n * m; ++j)
                if (table[i][j])
                    ++res;
        return res;
    };

    int ouf_number_of_pairs = check_grid(ouf);
    int ans_number_of_pairs = check_grid(ans);

    if (ouf_number_of_pairs <= ans_number_of_pairs)
        quitf(_ok, "correct");
    else {
        double weight = (double)1 / sqrt(ouf_number_of_pairs - ans_number_of_pairs + 1);
        exit_par(std::max(0.1, weight), ("q = " + std::to_string(ouf_number_of_pairs) + ", p = " + std::to_string(ans_number_of_pairs)).c_str());
    }
}
