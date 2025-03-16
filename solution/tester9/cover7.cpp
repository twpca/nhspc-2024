#include <bits/stdc++.h>
using namespace std;
#define pb emplace_back

using pii = pair<int, int>;
vector<vector<pii>> all;

// int all_id = 0;
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

  int lower = 8000;

  int id = 1;
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
  // all_id = mx_id;
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

  vector<vector<int>> ansp(n, vector<int>(m));
  auto get_subrect = [&](int x, int y, int h, int w) {
    vector<vector<int>> tmp(h, vector<int>(w));
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++)
        tmp[i][j] = g[x + i][y + j];
    return tmp;
  };
  int id = 0;
  auto paste_subrect = [&](int x, int y, int h, int w,
                           vector<vector<int>> &ret) {
    int mx_id = 0;
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++) {
        if (ret[i][j] == -1)
          continue;
        ret[i][j] = id + ret[i][j];
        mx_id = max(mx_id, ret[i][j]);
      }
    id = mx_id;
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++)
        ansp[x + i][y + j] = ret[i][j];
  };

  for (int x = 0; x < n; x += 5) {
    vector<int> dp(m / 5 + 1, 100000);
    dp[0] = 0;
    vector<vector<vector<int>>> src(m / 5 + 1);
    for (int i = 0; i < m / 5; i++) {
      auto tmp1 = get_subrect(x, i * 5, 5, 5);
      vector<vector<int>> src1 = solve(5, 5, tmp1);
      if (!src1.empty() && dp[i + 1] > dp[i]) {
        dp[i + 1] = dp[i];
        src[i + 1] = src1;
      }
      if (i + 1 < m / 5) {
        auto tmp2 = get_subrect(x, i * 5, 5, 10);
        vector<vector<int>> src2 = solve(5, 10, tmp2);
        if (dp[i + 2] > dp[i] + 1) {
          dp[i + 2] = dp[i] + 1;
          src[i + 2] = src2;
        }
      }
      /*if (i + 2 < m / 5) {
          auto tmp3 = get_subrect(x, i * 5, 5, 15);
          //cerr << "test " << x << " " << i << "\n";
          vector<vector<int>> src3 = solve(5, 15, tmp3);
          assert(!src3.empty());
          if (dp[i + 3] > dp[i] + 1) {
              dp[i + 3] = dp[i] + 1;
              src[i + 3] = src3;
          }
      }*/
    }

    for (int i = m / 5; i > 0;) {
      if ((int)src[i][0].size() == 5) {
        paste_subrect(x, (i - 1) * 5, 5, 5, src[i]);
        i--;
      } else if ((int)src[i][0].size() == 10) {
        paste_subrect(x, (i - 2) * 5, 5, 10, src[i]);
        i -= 2;
      } else {
        paste_subrect(x, (i - 3) * 5, 5, 15, src[i]);
        i -= 3;
      }
    }
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cout << ansp[i][j] << " \n"[j == m - 1];
}
