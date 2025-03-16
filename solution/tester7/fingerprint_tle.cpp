#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
ll const mod = 1e9 + 7;

void solve() {
    int m;
    cin >> m;

    vector<vector<int>> v(m + 1);
    vector<int> cnt(m + 1);
    auto is_leaf = [&](int x) { return cnt[x] == 1; };

    for (int i = 0; i < m - 1; i++) {
        int a, b;
        cin >> a >> b;
        v[a].emplace_back(b);
        v[b].emplace_back(a);
        cnt[a] += 1;
        cnt[b] += 1;
    }

    ll ans = 0;

    for (int i = 1; i <= m; i++) {
        if (!is_leaf(i)) continue;
        queue<int> bfs;
        bfs.emplace(i);
        vector<bool> vis(m + 1);
        ll dis = 0;
        while (bfs.size() > 0) {
            int t = bfs.size();
            dis += 1;
            while (t--) {
                auto cur = bfs.front();
                bfs.pop();
                vis[cur] = 1;

                for (int j : v[cur]) {
                    if (vis[j]) continue;
                    vis[j] = 1;

                    if (is_leaf(j) && j > i) {
                        ans += (dis * dis) % mod;
                        ans %= mod;
                    }
                    bfs.emplace(j);
                }
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    while (t--) {
        solve();
    }
}
