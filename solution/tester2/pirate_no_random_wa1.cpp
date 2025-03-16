#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <queue>

const int K = 1234, N = 10001;
int dis[K][N], d[N], que[N];

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

    int cnt = std::min(K, n);
    for (int iter = 0; iter < cnt; ++iter) {
        int x = iter + 1;
        std::fill(d + 1, d + n + 1, -1);
        d[x] = 0;
        que[0] = x;
        for (int i = 0, sz = 1; i < sz; ++i) {
            int v = que[i];
            for (int u : g[v]) {
                if (d[u] != -1)
                    continue;
                d[u] = d[v] + 1;
                que[sz++] = u;
            }
        }

        for (int i = 1; i <= n; ++i)
            dis[iter][i] = d[i];
    }

    for (int i = 1; i <= q; ++i) {
        int u, v;
        std::cin >> u >> v;
        int ans = n;
        for (int j = 0; j < cnt; ++j) {
            ans = std::min(ans, dis[j][u] + dis[j][v]);
        }
        std::cout << ans << " \n"[i == q];
    }
}