#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1'000'000'007;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<vector<int>> g(n + 1);
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  vector<ll> cnt(n + 1), sum(n + 1), sum2(n + 1);
  ll ans = 0;
  auto dfs1 = [&](auto dfs, int now, int p) -> void {
    if (int(g[now].size()) == 1)
      cnt[now] = 1;
    for (int i : g[now]) {
      if (i == p)
        continue;
      dfs(dfs, i, now);
      ll nsum = sum[i] + cnt[i];
      ll nsum2 = (sum2[i] + 2 * sum[i] + cnt[i]) % MOD;
      ll tmp =
          (sum2[now] * cnt[i] + cnt[now] * nsum2 + 2 * sum[now] * nsum) % MOD;
      ans += tmp;
      ans %= MOD;
      // cerr << "test " << now << " " << i << " : " << tmp << "\n";
      sum[now] += nsum;
      sum[now] %= MOD;
      sum2[now] += nsum2;
      sum2[now] %= MOD;
      cnt[now] += cnt[i];
    }
  };
  dfs1(dfs1, 1, 1);
  cout << ans << "\n";
}
