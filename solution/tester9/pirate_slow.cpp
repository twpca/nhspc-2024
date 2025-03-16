#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

mt19937 rnd(123123);

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
  vector<vector<pii>> qry(n + 1);
  for (int i = 0; i < Q; i++) {
    int u, v;
    cin >> u >> v;
    qry[u].emplace_back(pii(v, i));
  }
  vector<int> ans(Q, n);

  vector<int> dis(n + 1, -1);
  vector<vector<int>> pos(n + 1);
  queue<int> q;
  auto bfs = [&](int s) {
    fill(dis.begin(), dis.end(), -1);
    dis[s] = 0;
    q.push(s);
    for (auto [v, id] : qry[s])
      pos[v].emplace_back(id);
    while (!q.empty()) {
      int now = q.front();
      q.pop();
      for (int i : pos[now])
        ans[i] = min(ans[i], dis[now]);
      for (int i : g[now]) {
        if (dis[i] != -1)
          continue;
        dis[i] = dis[now] + 1;
        q.push(i);
      }
    }
    for (auto [v, id] : qry[s])
      pos[v].clear();
  };
  for (int i = 1; i <= n; i++)
    bfs(i);
  for (int i = 0; i < Q; i++)
    cout << ans[i] << " \n"[i == Q - 1];
}
