#include <iostream>
#include <vector>
#include <bitset>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cassert>

const int INF = 1e9;

#define TRAV(i, link, start) for (int i = link[start]; i != start; i = link[i])
template<bool E, const int NN, const int RR> // E: Exact, NN: num of 1s, RR: num of rows
struct DLX {
    int lt[NN], rg[NN], up[NN], dn[NN], rw[NN], cl[NN], bt[NN], s[NN], head, sz, ans;
    int rows, columns;
    bool vis[NN];
    std::bitset<RR> sol, cur;
    int weight[RR];
    void remove(int c) {
        if (E) lt[rg[c]] = lt[c], rg[lt[c]] = rg[c];
        TRAV(i, dn, c) {
            if (E) {
                TRAV(j, rg, i)
                    up[dn[j]] = up[j], dn[up[j]] = dn[j], --s[cl[j]];
            } else {
                lt[rg[i]] = lt[i], rg[lt[i]] = rg[i];
            }
        }
    }
    void restore(int c) {
        TRAV(i, up, c) {
            if (E) {
                TRAV(j, lt, i)
                    ++s[cl[j]], up[dn[j]] = j, dn[up[j]] = j;
            } else {
                lt[rg[i]] = rg[lt[i]] = i;
            }
        }
        if (E) lt[rg[c]] = c, rg[lt[c]] = c;
    }
    void init(int c) {
        rows = 0, columns = c;
        for (int i = 0; i < c; ++i) {
            up[i] = dn[i] = bt[i] = i;
            lt[i] = i == 0 ? c : i - 1;
            rg[i] = i == c - 1 ? c : i + 1;
            s[i] = 0;
        }
        rg[c] = 0, lt[c] = c - 1;
        up[c] = dn[c] = -1;
        head = c, sz = c + 1;
    }
    void insert(const std::vector<int> &col, int w) {
        if (col.empty()) return;
        int f = sz;
        for (int i = 0; i < (int)col.size(); ++i) {
            int c = col[i], v = sz++;
            dn[bt[c]] = v;
            up[v] = bt[c], bt[c] = v;
            rg[v] = (i + 1 == (int)col.size() ? f : v + 1);
            rw[v] = rows, cl[v] = c;
            ++s[c];
            if (i > 0) lt[v] = v - 1;
        }
        weight[rows++] = w, lt[f] = sz - 1;
    }
    int h() {
        int ret = 0;
        std::fill_n(vis, sz, false);
        TRAV(x, rg, head) {
            if (vis[x]) continue;
            vis[x] = true, ret += weight[x];
            TRAV(i, dn, x) TRAV(j, rg, i) vis[cl[j]] = true;
        }
        return ret;
    }
    void dfs(int dep) {
        if (ans != INF) return;
        if (rg[head] == head) return sol = cur, ans = dep, void();
        if (dn[rg[head]] == rg[head]) return;
        int w = rg[head];
        TRAV(x, rg, head) if (s[x] < s[w]) w = x;
        if (E) remove(w);
        TRAV(i, dn, w) {
            if (!E) remove(i);
            TRAV(j, rg, i) remove(E ? cl[j] : j);
            cur.set(rw[i]), dfs(dep + weight[rw[i]]), cur.reset(rw[i]);
            TRAV(j, lt, i) restore(E ? cl[j] : j);
            if (!E) restore(i);
        }
        if (E) restore(w);
    }
    int solve() {
        for (int i = 0; i < columns; ++i)
            dn[bt[i]] = i, up[i] = bt[i];
        ans = INF, sol.reset(), dfs(0);
        return ans;
    }
};

const int MAXN = 40;
const int MAXM = 40;

DLX<true, MAXN * MAXM * 5 * 5, MAXN * MAXM * 5 * 5 * 6> dlx;


int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> grid(n * 5, std::vector<int>(m * 5));
    for (auto &row : grid)
        for (int &v : row)
            std::cin >> v;
    
    std::vector<std::vector<std::pair<int, int>>> bricks;
    bricks.push_back({{0, 0}, {0, 1}, {1, 0}});
    bricks.push_back({{0, 0}, {0, 1}, {1, 1}});
    bricks.push_back({{0, 0}, {1, 0}, {1, 1}});
    bricks.push_back({{0, 0}, {1, 0}, {1, -1}});
    bricks.push_back({{0, 0}, {0, 1}, {0, 2}, {0, 3}});
    bricks.push_back({{0, 0}, {1, 0}, {2, 0}, {3, 0}});
    
    std::vector<int> block_vis(n * m);
    int block_vis_cnt = 0;
   
    std::vector<std::vector<int>> current(n * 5, std::vector<int>(m * 5));
    int current_cnt = 0;

    std::vector<std::vector<int>> number(n * 5, std::vector<int>(m * 5));
    
    auto in_range = [&](int x, int y) {
        return !(x < 0 || y < 0 || x >= 5 * n || y >= 5 * m); 
    };
    auto check = [&](int x, int y) {
        return !(!in_range(x, y) || current[x][y] != current_cnt); 
    };
    auto block = [&](int x, int y) {
        return x / 5 * m + y / 5;  
    };
    auto hblock = [&](int x, int y) {
        return x * m + y;  
    };
    auto decode = [&](int bid) {
        return std::make_pair(bid / m * 5, bid % m * 5);
    };
    auto hdecode = [&](int bid) {
        return std::make_pair(bid / m, bid % m);
    };

    std::vector<int> color(15000);
    std::iota(color.begin(), color.end(), 1);
    std::reverse(color.begin(), color.end());
    std::vector<int> color_vis(15001);
    int color_vis_cnt = 0;
   
    auto solver = [&](std::vector<int> blocks) {
        ++current_cnt;
        std::vector<std::pair<int, int>> rev_pos;
        for (int b : blocks) {
            auto [x, y] = decode(b);
            for (int i = x; i < x + 5; ++i)
                for (int j = y; j < y + 5; ++j)
                    if (grid[i][j] != -1) {
                        number[i][j] = rev_pos.size();
                        rev_pos.emplace_back(i, j);
                        current[i][j] = current_cnt;
                    }
        }
        dlx.init(rev_pos.size());
        std::vector<std::vector<int>> rows;
        for (int b : blocks) {
            auto [x, y] = decode(b);
            for (int i = x; i < x + 5; ++i)
                for (int j = y; j < y + 5; ++j)
                    for (auto brick : bricks) {
                        ++block_vis_cnt;
                        int region = 0, valid = 1;
                        std::vector<int> col;
                        for (auto [dx, dy] : brick) {
                            if (!check(i + dx, j + dy)) {
                                valid = 0;
                                break;
                            }
                            region += block_vis[block(i + dx, j + dy)] != block_vis_cnt;
                            block_vis[block(i + dx, j + dy)] = block_vis_cnt;
                            col.push_back(number[i + dx][j + dy]);
                        }
                        if (valid) {
                            dlx.insert(col, region - 1);
                            rows.push_back(col);
                        }
                    }
        }

        ++color_vis_cnt;
        for (int b : blocks) {
            auto [x, y] = decode(b);
            for (int i = x; i < x + 5; ++i)
                for (int j = y; j < y + 5; ++j)
                    if (grid[i][j] > 0 && color_vis[grid[i][j]] != color_vis_cnt) {
                        color.push_back(grid[i][j]);
                        color_vis[grid[i][j]] = color_vis_cnt; 
                    }
        }
        
        int res = dlx.solve();
        for (int i = 0; i < int(rows.size()); ++i)
            if (dlx.sol[i]) {
                for (int c : rows[i]) {
                    auto [x, y] = rev_pos[c];
                    grid[x][y] = color.back();
                }
                color.pop_back();
            }
    
        return res;
    };
    
    std::vector<int> black(n * m), matching(n * m, -1), vis(n * m);
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (solver({hblock(i, j)}) == INF)
                black[hblock(i, j)] = 1; 

    auto dfs = [&](auto _dfs, int u, bool force_black) -> bool {
        vis[u] = 1;
        auto [x, y] = hdecode(u);
        for (int i = 0; i < 4; ++i)
            if (in_range((x + dx[i]) * 5, (y + dy[i]) * 5)) {
                int v = hblock(x + dx[i], y + dy[i]);
                if (force_black && !black[v]) continue;
                if (!~matching[v] || (!vis[matching[v]] && _dfs(_dfs, matching[v], force_black)))
                    return matching[matching[u] = v] = u, true;
            }
        return false;
    };

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int u = hblock(i, j);
            if (black[u] && matching[u] == -1) {
                std::fill(vis.begin(), vis.end(), 0);
                dfs(dfs, u, true);
            }
        }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            int u = hblock(i, j);
            if (black[u] && matching[u] == -1) {
                std::fill(vis.begin(), vis.end(), 0);
                assert(dfs(dfs, u, false));
            }
        }

    int ans = 0;
    for (int i = 0; i < n * m; ++i)
        if (matching[i] != -1) {
            assert(solver({i, matching[i]}) != INF);
            matching[i] = matching[matching[i]] = -1;
            ++ans;
        }
    std::cerr << "total: " << ans << "\n";

    for (int i = 0; i < n * 5; ++i)
        for (int j = 0; j < m * 5; ++j)
            std::cout << grid[i][j] << " \n"[j + 1 == 5 * m];
}
