#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector <std::vector <int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector <int> dep(n + 1, -1);
    auto dfs = [&](auto &self, int v) -> void {
        for (int u : g[v])
            if (dep[u] == -1) {
                dep[u] = dep[v] + 1;
                self(self, u);
            }
    };
    int root = 1;
    dep[root] = 0;
    dfs(dfs, root);

    int K = (int(sqrt(n)) + 5) / 2;

    std::vector <int> cnt(n + 1);
    for (int i = 1; i <= n; ++i)
        cnt[dep[i] % K]++;

    int mn = int(std::min_element(cnt.begin(), cnt.begin() + K) - cnt.begin());

    std::vector <std::vector <int>> dis;
    for (int x = 1; x <= n; ++x) {
        if (cnt[x] % K != mn && x != root) 
            continue;
        std::vector <int> d(n + 1, -1), que;
        d[x] = 0;
        que.push_back(x);
        for (int i = 0; i < (int)que.size(); ++i) {
            int v = que[i];
            for (int u : g[v]) {
                if (d[u] != -1)
                    continue;
                d[u] = d[v] + 1;
                que.push_back(u);
            }
        }
        dis.push_back(d);
    }

    for (int i = 1; i <= q; ++i) {
        int u, v;
        std::cin >> u >> v;
        int ans = n;
        for (int j = 0; j < (int)dis.size(); ++j) {
            ans = std::min(ans, dis[j][u] + dis[j][v]);
        }
        std::cout << ans << " \n"[i == q];
    }
}