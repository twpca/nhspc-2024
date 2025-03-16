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
  vector<pii> qry(Q);
  for (int i = 0; i < Q; i++)
    cin >> qry[i].first >> qry[i].second;
  vector<int> ans(Q, n);

  vector<int> dis(n + 1, -1);
  queue<int> q;
  auto bfs = [&]() {
    int s = rnd() % n + 1;
    fill(dis.begin(), dis.end(), -1);
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
    for (int i = 0; i < Q; i++) {
      auto [u, v] = qry[i];
      ans[i] = min(ans[i], dis[u] + dis[v]);
    }
  };
  for (int i = 0; i < 1300; i++)
    bfs();
  for (int i = 0; i < Q; i++)
    cout << ans[i] << " \n"[i == Q - 1];
}
