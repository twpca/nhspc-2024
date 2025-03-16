#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
  auto dfs1 = [&](auto dfs, int now, int p, ll d) -> void {
    if (int(g[now].size()) == 1)
      ans += d * d;
    for (int i : g[now]) {
      if (i == p)
        continue;
      dfs(dfs, i, now, d + 1);
    }
  };
  for (int i = 1; i <= n; i++)
    if (int(g[i].size()) == 1)
      dfs1(dfs1, i, i, 0);
  ans /= 2;
  cout << ans << "\n";
}
