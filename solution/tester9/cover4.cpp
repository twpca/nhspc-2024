#include <bits/stdc++.h>
using namespace std;
#define pb emplace_back

using pii = pair<int, int>;
vector<vector<pii>> all;

int all_id = 0;
vector<vector<int>> solve(int n, int m, vector<vector<int>> g) {
  auto calc = [&]() {
    vector share(n * m / 25, vector<int>(n * m / 25));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (i + 1 < n && g[i][j] == g[i + 1][j])
          share[i / 5 * (m / 5) + j / 5][(i + 1) / 5 * (m / 5) + j / 5] = 1;
        if (j + 1 < m && g[i][j] == g[i][j + 1])
          share[i / 5 * (m / 5) + j / 5][i / 5 * (m / 5) + (j + 1) / 5] = 1;
      }
    }
    int cnt = 0;
    for (int i = 0; i < n * m / 25; i++)
      for (int j = i + 1; j < n * m / 25; j++)
        cnt += share[i][j];
    cerr << "calc " << cnt << "\n";
    return cnt;
  };

  int ans = 8787;
  vector<vector<int>> ansp;

  int lower = 2;

  int id = all_id;
  int mx_id = -1;
  auto dfs1 = [&](auto dfs, int x, int y) -> void {
    if (y == m)
      x++, y = 0;
    if (x == n) {
      int score = calc();
      if (score >= ans)
        return;
      ans = score;
      ansp = g;
      mx_id = id;
      return;
    }
    if (g[x][y] != 0) {
      dfs(dfs, x, y + 1);
      return;
    }

    for (auto &sol : all) {
      bool ok = true;
      for (auto [dx, dy] : sol) {
        int nx = x + dx, ny = y + dy;
        if (nx < 0 || n <= nx || ny < 0 || m <= ny || g[nx][ny]) {
          ok = false;
          break;
        }
      }
      if (!ok)
        continue;
      id++;
      for (auto [dx, dy] : sol) {
        int nx = x + dx, ny = y + dy;
        g[nx][ny] = id;
      }
      dfs(dfs, x, y + 1);
      if (ans <= lower)
        return;
      for (auto [dx, dy] : sol) {
        int nx = x + dx, ny = y + dy;
        g[nx][ny] = 0;
      }
      id--;
    }
  };
  dfs1(dfs1, 0, 0);
  all_id = mx_id;
  return ansp;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  all.pb(vector<pii>({pii(0, 0), pii(0, 1), pii(1, 1)}));
  all.pb(vector<pii>({pii(0, 0), pii(0, 1), pii(1, 0)}));
  all.pb(vector<pii>({pii(0, 0), pii(1, 0), pii(1, 1)}));
  all.pb(vector<pii>({pii(0, 0), pii(1, -1), pii(1, 0)}));
  all.pb(vector<pii>({pii(0, 0), pii(0, 1), pii(0, 2), pii(0, 3)}));
  all.pb(vector<pii>({pii(0, 0), pii(1, 0), pii(2, 0), pii(3, 0)}));

  int n, m;
  cin >> n >> m;
  n *= 5;
  m *= 5;
  vector g(n, vector<int>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> g[i][j];

  vector<vector<int>> ansp = solve(n, m, g);
  /*vector<vector<int>> ansp(n, vector<int>(m));
  for (int i = 0; i < n; i += 5)
          for (int j = 0; j < m; j += 5) {
                  vector<vector<int>> tmp(5, vector<int>(5));
                  for (int x = 0; x < 5; x++)
                          for (int y = 0; y < 5; y++)
                                  tmp[x][y] = g[i + x][j + y];
                  auto ret = solve(5, 5, tmp);
                  for (int x = 0; x < 5; x++)
                          for (int y = 0; y < 5; y++)
                                  ansp[i + x][j + y] = ret[x][y];
          }*/

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cout << ansp[i][j] << " \n"[j == m - 1];
}
