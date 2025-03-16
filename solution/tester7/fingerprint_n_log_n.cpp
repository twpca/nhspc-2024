#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) signed(size(x))
ll const mod = 1e9 + 7;
struct CD {
  int n;
  vector<vector<int>> adj;
  vector<int> si, mxs, vis, dep;

  CD(int _n) : n(_n), adj(n), dep(n) {
    si = mxs = vis = dep;
  }

  void add(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  int rt;
  void dfs(int cur, int fa = -1) {
    si[cur] = 1, mxs[cur] = 0;
    dep[cur] = (fa == -1 ? 0 : dep[fa] + 1);
    for (int nxt : adj[cur]) {
      if (nxt == fa || vis[nxt]) continue;
      dfs(nxt, cur);
      si[cur] += si[nxt];
      mxs[cur] = max(mxs[cur], si[nxt]);
    }
    mxs[cur] = max(mxs[cur], n - si[cur]);
    if (rt == -1 || mxs[cur] < mxs[rt]) rt = cur;
  }

  vector<int> in;
  ll solve(int cur) {
    rt = -1;
    dfs(cur), dfs(rt);
    cur = rt;
    vis[cur] = 1;

    vector<vector<int>> parti;
    int lst = sz(in);
    ll ret = 0;
    for (int nxt : adj[cur]) {
      if (vis[nxt]) continue;
      n = si[nxt];
      ret += solve(nxt);
      parti.emplace_back();
      for (; lst < sz(in); ++lst) {
        parti.back().emplace_back(in[lst]);
        vis[in[lst]] = 0;
      }
    }

    dfs(cur);

    if (sz(adj[cur]) == 1) parti.emplace_back(1, cur);

    int m = sz(parti);
    vector<ll> cnt(m), sum1(m), sum2(m);
    ll tot_cnt = 0, tot_sum1 = 0, tot_sum2 = 0;
    for (int i = 0; i < m; ++i) {
      for (int j : parti[i]) {
        if (sz(adj[j]) != 1) continue;
        ++cnt[i];
        sum1[i] += dep[j];
        sum2[i] += 1LL * dep[j] * dep[j];
      }
      tot_cnt += cnt[i];
      tot_cnt %= mod;
      tot_sum1 += sum1[i];
      tot_sum1 %= mod;
      tot_sum2 += sum2[i];
      tot_sum2 %= mod;
    }

    for (int i = 0; i < m; ++i) {
      tot_cnt -= cnt[i];
      tot_cnt %= mod;
      if (tot_cnt < 0)
          tot_cnt += mod;
      tot_sum1 -= sum1[i];
      tot_sum2 -= sum2[i];
      ret += tot_sum2 * cnt[i] + 2 * tot_sum1 * sum1[i] + (tot_cnt * sum2[i]) % mod;
      ret %= mod;
    }

    in.emplace_back(cur);
    return ret;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  CD solver(n);
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    solver.add(u - 1, v - 1);
  }

  cout << solver.solve(0) << '\n';
}
