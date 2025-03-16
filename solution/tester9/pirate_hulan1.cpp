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

  int K = sqrt(n) / 2 + 1;

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

  vector<vector<int>> all_dis;
  auto bfs = [&](int s) {
    queue<int> q;
    vector<int> dis(n + 1, -1);
    dis[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int now = q.front();
      q.pop();
      for (int i : g[now]) {
        if (dis[i] != -1)
          continue;
        dis[i] = dis[now] + 1;
        q.push(i);
      }
    }
    return dis;
  };
  for (int i : special)
    all_dis.emplace_back(bfs(i));

  while (Q--) {
    int u, v;
    cin >> u >> v;
    int ans = n;
    for (auto &dis : all_dis) {
      ans = min(ans, dis[u] + dis[v]);
    }
    cout << ans << " \n"[Q == 0];
  }
}
