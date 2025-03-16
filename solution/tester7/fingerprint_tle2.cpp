#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
using info = array<ll, 3>;  // 0 : cnt, 1 : sum, 2 : sum of square
const ll mod = 1e9 + 7;
void solve() {
    int m;
    cin >> m;

    vector<vector<int>> v(m + 1);
    vector<int> cnt(m + 1);
    auto is_leaf = [&](int x) { return cnt[x] == 1; };

    for (int i = 0; i < m - 1; i++) {
        int a, b;
        cin >> a >> b;
        v[b].emplace_back(a);
        v[a].emplace_back(b);
        cnt[a] += 1;
        cnt[b] += 1;
    }

    ll ans = 0;
    vector<bool> vis(m + 1);
    auto dfs = [&](auto const& self, int cur, int pre) -> info {
        info ret = {0, 0, 0};
        vector<info> rec;
        for (int i : v[cur]) {
            if (i == pre) {
                continue;
            }
            rec.emplace_back(self(self, i, cur));
        }
        int n = rec.size();
        for (int i = 0; i < n; i++) {
            rec[i][2] = (rec[i][2] + rec[i][0] + 2 * rec[i][1]) % mod;
            rec[i][1] = (rec[i][1] + rec[i][0]) % mod;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans = (ans + (rec[i][2] * rec[j][0]) % mod + (rec[i][0] * rec[j][2]) % mod) % mod;
                ans = (ans + 2 * rec[i][1] * rec[j][1]) % mod;
            }
            for (int j = 0; j < 3; j++) {
                ret[j] += rec[i][j];
                ret[j] %= mod;
            }
        }
        if (is_leaf(cur) && rec.size() == 1) {
            ans += rec.back()[2];
        }

        if (is_leaf(cur)) {
            ret[0] += 1;
        }
        return ret;
    };

    dfs(dfs, 1, -3);
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    while (t--) {
        solve();
    }
}
