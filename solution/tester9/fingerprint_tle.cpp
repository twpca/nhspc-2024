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

  vector<int> leaf;
  for (int i = 1; i <= n; i++) {
    if (int(g[i].size()) == 1)
      leaf.emplace_back(i);
  }

  ll ans = 0;
  vector<int> dpt(n + 1), in(n + 1), out(n + 1);
  vector anc(20, vector<int>(n + 1));
  int ts = 0;
  auto dfs1 = [&](auto dfs, int now, int p) -> void {
    in[now] = ts++;
    anc[0][now] = p;
    for (int i : g[now]) {
      if (i == p)
        continue;
      dpt[i] = dpt[now] + 1;
      dfs(dfs, i, now);
    }
    out[now] = ts++;
  };
  dfs1(dfs1, 1, 1);

  for (int i = 1; i < 20; i++)
    for (int j = 1; j <= n; j++)
      anc[i][j] = anc[i - 1][anc[i - 1][j]];
  auto isAnc = [&](int a, int b) { return in[a] <= in[b] && out[b] <= out[a]; };
  auto getlca = [&](int a, int b) {
    if (isAnc(a, b))
      return a;
    for (int i = 19; i >= 0; i--)
      if (!isAnc(anc[i][a], b))
        a = anc[i][a];
    return anc[0][a];
  };
  for (int i : leaf)
    for (int j : leaf) {
      int lca = getlca(i, j);
      int d = dpt[i] + dpt[j] - 2 * dpt[lca];
      ans += (long long)d * d % MOD;
      ans %= MOD;
    }
  ans /= 2;

  cout << ans << "\n";
}
