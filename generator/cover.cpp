#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <numeric>
#include <fstream>
#include <functional>
#include <utility>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <queue>
#include "testlib.h"

int T;
std::vector<std::vector<std::pair<int, int>>> cells;
std::vector<std::vector<int>> table;
std::vector<int> bad, good, two, single;

void init() {
    std::fstream fs;
    fs.open("table.txt", std::fstream::in);
    fs >> T;
    cells.resize(T);
    for (int i = 0; i < T; ++i) {
        auto &v = cells[i];
        int k;
        fs >> k;
        v.resize(k);
        for (auto &[x, y] : v)
            fs >> x >> y;
        std::sort(v.begin(), v.end());
        if (k == 1)
            single.push_back(i);
        else if (k == 2)
            two.push_back(i);
    }
    int bsz;
    fs >> bsz;
    bad.resize(bsz);
    for (int &i : bad)
        fs >> i;
    for (int i = 0; i < T; ++i) {
        if (int(cells[i].size()) < 2 || std::find(bad.begin(), bad.end(), i) != bad.end())
            continue;
        good.push_back(i);
    }
    table.resize(T, std::vector<int>(T));
    for (auto &v : table)
        for (int &i : v)
            fs >> i;
}

bool valid(int i, int j, int dx, int dy) {
    for (auto [a, b] : cells[i])
        for (auto [x, y] : cells[j])
            if (std::max(std::abs(a - (x + dx)), std::abs(b - (y + dy))) <= 1)
                return false;
    return true;
}

std::vector<std::vector<int>> rnd_assign(std::vector<std::vector<int>> req) {
    int n = req.size(), m = req[0].size();
    std::vector<std::vector<int>> num(n, std::vector<int>(m, -1)), res(n * 5, std::vector<int>(m * 5));
    std::vector<int> idx(n * m);
    std::iota(idx.begin(), idx.end(), 0);
    shuffle(idx.begin(), idx.end());

    auto number = [&](int x, int y) {
        if (x < 0 || y < 0 || x >= n || y >= m) return -1;
        return num[x][y];
    };

    int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    for (int done = 0, cnt = 0; !done;) {
        std::vector<std::vector<int>>(n, std::vector<int>(m, -1)).swap(num);
        std::vector<std::vector<int>>(n * 5, std::vector<int>(m * 5, 0)).swap(res);
        done = 1;
        for (int i : idx) {
            int x = i / m, y = i % m;
            std::vector<int> pool;

            auto try_push = [&](int u) {
                for (int d = 0; d < 8; ++d) {
                    int v = number(x + dx[d], y + dy[d]);
                    if (v != -1 && !valid(u, v, dx[d] * 5, dy[d] * 5))
                        return;
                }
                pool.push_back(u);
            };

            if (req[x][y] == -1) {
                for (int j : bad)
                    try_push(j);
            }
            else if (req[x][y] == 0) {
                for (int j = 0; j < T; ++j)
                    try_push(j);
            }
            else if (req[x][y] == 1) {
                for (int j : single)
                    try_push(j);
            }
            else if (req[x][y] == 2) {
                for (int j : two)
                    try_push(j);
            }
            else if (req[x][y] == 3) {
                for (int j : good)
                    try_push(j);
            }
            else
                assert(0);
            if (pool.empty()) { 
                done = 0;
                std::cerr << "Fail " << ++cnt << std::endl;
            }
            int u = pool[rnd.next(0, int(pool.size()) - 1)];
            num[x][y] = u;
            for (auto [a, b] : cells[u])
                res[x * 5 + a][y * 5 + b] = -1;
        }
    }
    return res;
}

std::vector<std::vector<int>> gen1() {
    rnd.next(0, 2);
    rnd.next(0, 2);
    return rnd_assign(std::vector<std::vector<int>>(1, std::vector<int>(1, 3)));
}

std::vector<std::vector<int>> gen2() {
    std::pair<int, int> mx = std::make_pair(0, 0);
    for (int i = 0; i < T; ++i)
        for (int j = 0; j < T; ++j)
            if (valid(i, j, 0, 5) && table[i][j] > table[mx.first][mx.second])
                mx = std::make_pair(i, j);
    std::vector<std::vector<int>> grid(5, std::vector<int>(10));
    for (auto [x, y] : cells[mx.first])
        grid[x][y] = -1;
    for (auto [x, y] : cells[mx.second])
        grid[x][y + 5] = -1;
    return grid;
}

std::vector<std::vector<int>> gen3() {
    return rnd_assign(std::vector<std::vector<int>>(1, std::vector<int>(3, -1)));
}

std::vector<std::vector<int>> gen4() {
    std::vector<std::vector<int>> req(2, std::vector<int>(2, -1));
    req[1][0] = 1;
    return rnd_assign(req);
}

std::vector<std::vector<int>> gen5() {
    std::vector<std::vector<int>> req(10, std::vector<int>(10, 1));
    return rnd_assign(req);
}

std::vector<std::vector<int>> gen6() {
    std::vector<std::vector<int>> req(10, std::vector<int>(10, 1));
    for (int x = 0; x < 10; ++x)
        for (int y = x & 1; y < 10; y += 2)
            if (rnd.next(1, 100) <= 20)
                req[x][y] = -1;
            else
                req[x][y] = 2;
    return rnd_assign(req);
}

std::vector<std::vector<int>> gen7() {
    std::vector<std::vector<int>> req(1, std::vector<int>(1599, 0));
    for (int i = 0; i < 39; ++i) {
        if (rnd.next(1, 100) <= 20)
            req[0][i] = -1;
    }
    return rnd_assign(req);
}

std::vector<std::vector<int>> gen_components(int n, int m, int gap, int k) {
    std::vector<std::vector<int>> req(n, std::vector<int>(m, 3));
    std::vector<std::pair<int, int>> idx;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            idx.emplace_back(i, j);
    shuffle(idx.begin(), idx.end());

    std::vector<std::vector<int>> done(n, std::vector<int>(m));
    std::vector<std::vector<int>> dis(n, std::vector<int>(m));

    auto check = [&](int x, int y) {
        return !(x < 0 || y < 0 || x >= n || y >= m || done[x][y]);  
    };
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

    for (auto start : idx) {
        if (done[start.first][start.second]) continue;
        std::vector<std::pair<int, int>> pool;

        auto push = [&](int x, int y) {
            pool.emplace_back(x, y);
            done[x][y] = 1;
        };

        push(start.first, start.second);
        int block = rnd.next(1, k);
        for (int i = 0; !pool.empty() && i < block; ++i) {
            int u = rnd.next(0, int(pool.size()) - 1);
            std::swap(pool[u], pool.back());
            auto [x, y] = pool.back();
            pool.pop_back();
            req[x][y] = -1;
            for (int j = 0; j < 4; ++j)
                if (check(x + dx[j], y + dy[j]))
                    push(x + dx[j], y + dy[j]);
        }
        std::queue<std::pair<int, int>> que;
        for (auto [x, y] : pool)
            dis[x][y] = 1, que.emplace(x, y);
        while (!que.empty()) {
            auto [x, y] = que.front();
            que.pop();
            if (dis[x][y] < gap) {
                for (int j = 0; j < 4; ++j)
                    if (check(x + dx[j], y + dy[j])) {
                        que.emplace(x + dx[j], y + dy[j]);
                        done[x + dx[j]][y + dy[j]] = 1;
                        dis[x + dx[j]][y + dy[j]] = dis[x][y] + 1;
                    }
            }
        }
    }
    return req;
}

std::vector<std::vector<int>> gen8() {
    return rnd_assign(gen_components(20, 24, 3, 10));
}

std::vector<std::vector<int>> gen9() {
    return rnd_assign(gen_components(40, 40, 1, 20));
}

std::vector<std::vector<int>> gen10() {
    std::vector<std::vector<int>> req(39, std::vector<int>(39, -1));
    return rnd_assign(req);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int testcases = atoi(argv[1]);

    init();

    std::vector<std::function<std::vector<std::vector<int>>()>> func = {
        gen1,
        gen2,  
        gen3, 
        gen4, 
        gen5, 
        gen6, 
        gen7, 
        gen8, 
        gen9, 
        gen10, 
    };

    std::fstream out(std::to_string(testcases) + ".in", std::fstream::out);
    auto grid = func[testcases - 1]();
    out << grid.size() / 5 << " " << grid[0].size() / 5 << "\n";
    for (auto &row : grid)
        for (int i = 0; i < int(row.size()); ++i)
            out << row[i] << " \n"[i + 1 == int(row.size())];
    return 0;
}
