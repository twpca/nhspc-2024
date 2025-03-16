#include <iostream>
#include <vector>
#include <cassert>

int main() {
    int n, m;
    std::cin >> n >> m;
    n *= 5, m *= 5; 
    std::vector <std::vector <int>> a(n, std::vector <int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
        }
    }

    std::vector <std::vector <std::pair <int, int>>> cur;
    cur.push_back({std::make_pair(0, 1), std::make_pair(1, 1)});
    cur.push_back({std::make_pair(0, 1), std::make_pair(1, 0)});
    cur.push_back({std::make_pair(1, 0), std::make_pair(1, 1)});
    cur.push_back({std::make_pair(1, -1), std::make_pair(1, 0)});
    cur.push_back({std::make_pair(1, 0), std::make_pair(2, 0), std::make_pair(3, 0)});
    cur.push_back({std::make_pair(0, 1), std::make_pair(0, 2), std::make_pair(0, 3)});
    int id = 1;
    auto dfs = [&](auto self, int x, int y, int lx, int rx, int ly, int ry) -> bool {
        if (y == ry) {
            return self(self, x + 1, ly, lx, rx, ly, ry);
        } else if (x == rx) {
            return true;
        } else if (a[x][y] != 0) {
            return self(self, x, y + 1, lx, rx, ly, ry);
        } else {
            for (int i = 0; i < 6; ++i) {
                bool ok = true;
                for (auto [dx, dy] : cur[i]) {
                    ok &= lx <= x + dx && x + dx < rx && ly <= y + dy && y + dy < ry && a[x + dx][y + dy] == 0;
                }
                if (ok) {
                    a[x][y] = id;
                    for (auto [dx, dy] : cur[i]) {
                        a[x + dx][y + dy] = id;
                    }
                    id++;
                    if (self(self, x, y + 1, lx, rx, ly, ry)) {
                        return true;
                    }
                    id--;
                    for (auto [dx, dy] : cur[i]) {
                        a[x + dx][y + dy] = 0;
                    }
                    a[x][y] = 0;
                }
            }
        }
        return false;
    };
    
    auto dfs2 = [&](auto self, int x, int y) -> bool {
        if (y == m / 5) {
            return self(self, x + 1, 0);
        } else if (x == n / 5) {
            return true;
        } else {
            bool all_placed = true;
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    all_placed &= a[x * 5 + i][y * 5 + j] != 0;
                }
            }
            if (all_placed) {
                return self(self, x, y + 1);
            } else {
                std::vector <std::pair<int, int>> rect;
                rect.push_back(std::make_pair(1, 1));
                rect.push_back(std::make_pair(1, 2));
                rect.push_back(std::make_pair(2, 1));
                rect.push_back(std::make_pair(1, 3));
                rect.push_back(std::make_pair(3, 1));
                rect.push_back(std::make_pair(2, 2));
                for (auto [i, j] : rect) {
                    if (x + i > n / 5 || y + j > m / 5)
                        continue;
                    if (dfs(dfs, x * 5, y * 5, x * 5, (x + i) * 5, y * 5, (y + j) * 5)) {
                        if (self(self, x, y + 1)) 
                            return true;
                        for (int ii = x * 5; ii < (x + i) * 5; ++ii) {
                            for (int jj = y * 5; jj < (y + j) * 5; ++jj) {
                                if (a[ii][jj] != -1) {
                                    while (id > a[ii][jj])
                                        id--;
                                    a[ii][jj] = 0;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }
    };
    assert(dfs2(dfs2, 0, 0)); 

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << a[i][j] << " \n"[j + 1 == m];
        }
    }
}