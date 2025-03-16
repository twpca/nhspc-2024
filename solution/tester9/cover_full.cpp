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

vector<pii> dir = {pii(1, 0), pii(0, 1), pii(-1, 0), pii(0, -1)};

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

  vector<vector<bool>> good(n / 5, vector<bool>(m / 5));
  for (int i = 0; i < n; i += 5)
    for (int j = 0; j < m; j += 5) {
      auto tmp = get_subrect(i, j, 5, 5);
      auto ret = solve(5, 5, tmp);
      if (!ret.empty())
        good[i / 5][j / 5] = true;
    }

  vector<vector<pii>> mat(n / 5, vector<pii>(m / 5, pii(-1, -1)));
  vector vst(n / 5, vector<bool>(m / 5));
  auto reset = [&]() {
    for (int i = 0; i < n / 5; i++)
      fill(vst[i].begin(), vst[i].end(), false);
  };
  auto dfs1 = [&](auto dfs, int x, int y, bool bad) -> bool {
    vst[x][y] = true;
    for (auto [dx, dy] : dir) {
      int nx = x + dx, ny = y + dy;
      if (nx < 0 || n / 5 <= nx || ny < 0 || m / 5 <= ny)
        continue;
      if (bad && good[nx][ny])
        continue;
      auto [tx, ty] = mat[nx][ny];
      if (tx == -1 || (!vst[tx][ty] && dfs(dfs, tx, ty, bad))) {
        mat[nx][ny] = pii(x, y);
        mat[x][y] = pii(nx, ny);
        return true;
      }
    }
    return false;
  };
  for (int i = 0; i < n / 5; i++)
    for (int j = 0; j < m / 5; j++) {
      if (good[i][j] || mat[i][j].first != -1)
        continue;
      reset();
      dfs1(dfs1, i, j, true);
    }
  for (int i = 0; i < n / 5; i++)
    for (int j = 0; j < m / 5; j++) {
      if (good[i][j] || mat[i][j].first != -1)
        continue;
      reset();
      dfs1(dfs1, i, j, false);
    }
  // for (int i = 0; i < n / 5; i++) pary(mat[i].begin(), mat[i].end());

  for (int i = 0; i < n / 5; i++) {
    for (int j = 0; j < m / 5; j++) {
      if (mat[i][j] == pii(-1, -1)) {
        auto tmp = get_subrect(i * 5, j * 5, 5, 5);
        auto ret = solve(5, 5, tmp);
        if (ret.empty()) {
          tmp = get_subrect(i * 5, (j - 2) * 5, 5, 15);
          ret = solve(5, 15, tmp);
          paste_subrect(i * 5, (j - 2) * 5, 5, 15, ret);
        } else
          paste_subrect(i * 5, j * 5, 5, 5, ret);
      } else if (mat[i][j] == pii(i + 1, j)) {
        auto tmp = get_subrect(i * 5, j * 5, 10, 5);
        auto ret = solve(10, 5, tmp);
        paste_subrect(i * 5, j * 5, 10, 5, ret);
      } else if (mat[i][j] == pii(i, j + 1)) {
        auto tmp = get_subrect(i * 5, j * 5, 5, 10);
        auto ret = solve(5, 10, tmp);
        paste_subrect(i * 5, j * 5, 5, 10, ret);
      }
    }
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cout << ansp[i][j] << " \n"[j == m - 1];
}
