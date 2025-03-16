#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n, m, Q;
  cin >> n >> m >> Q;
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  vector<pii> qry(Q);
  for (int i = 0; i < Q; i++)
    cin >> qry[i].first >> qry[i].second;
  vector<int> ans(Q, n);

  vector<vector<int>> sub(n + 1);
  {
    vector<bool> vst(n + 1);
    queue<int> q;
    q.push(1);
    vst[1] = true;
    while (!q.empty()) {
      int now = q.front();
      q.pop();
      for (int i : g[now]) {
        if (vst[i])
          continue;
        sub[now].emplace_back(i);
        vst[i] = true;
        q.push(i);
      }
    }
  }

  int K = sqrt(n) / 8;

  vector<int> special;
  auto dfs1 = [&](auto dfs, int now) -> pii {
    int far = 0, closest = n + 1;
    for (int i : sub[now]) {
      auto [type, dis] = dfs(dfs, i);
      if (type == 0)
        far = max(far, dis + 1);
      else
        closest = min(closest, dis + 1);
    }
    if (closest + far > K) {
      if (far == K) {
        special.emplace_back(now);
        return pii(1, 0);
      }
      return pii(0, far);
    } else
      return pii(1, closest);
  };
  dfs1(dfs1, 1);

  auto bfs = [&](int s) {
    queue<int> q;
    vector<int> dis(n + 1, -1);
    vector<vector<int>> sub(n + 1);
    dis[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int now = q.front();
      q.pop();
      for (int i : g[now]) {
        if (dis[i] != -1)
          continue;
        sub[now].emplace_back(i);
        dis[i] = dis[now] + 1;
        q.push(i);
      }
    }

    vector<int> in(n + 1), out(n + 1);
    int ts = 0;
    auto dfs2 = [&](auto dfs, int now) -> void {
      in[now] = ts++;
      for (int i : sub[now]) {
        dfs(dfs, i);
      }
      out[now] = ts++;
    };
    dfs2(dfs2, s);
    auto isAnc = [&](int a, int b) {
      return in[a] <= in[b] && out[b] <= out[a];
    };

    for (int i = 0; i < Q; i++) {
      auto [u, v] = qry[i];
      if (isAnc(u, v))
        ans[i] = min(ans[i], dis[v] - dis[u]);
      if (isAnc(v, u))
        ans[i] = min(ans[i], dis[u] - dis[v]);
      ans[i] = min(ans[i], dis[v] + dis[u]);
    }
  };
  for (int i : special)
    bfs(i);

  for (int i = 0; i < Q; i++)
    cout << ans[i] << " \n"[i == Q - 1];
}
