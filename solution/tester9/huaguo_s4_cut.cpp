#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

int sum_ans = 0;
void solve() {
  int n, K;
  cin >> n >> K;
  K %= n;

  map<int, int> st;
  vector<int> a(n + 1);
  a[0] = -1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] != a[i - 1])
      st[i] = a[i] - a[i - 1];
  }

  auto modify = [&](int x, int val) {
    st[x] += val;
    if (st[x] == 0)
      st.erase(x);
  };

  int ans = 0;
  while (int(st.size()) >= 2) {
    ans++;
    if (sum_ans + ans > 100000) {
      ans = -1;
      break;
    }
    modify(1, 1);
    auto it = st.upper_bound(K);
    it--;
    int cur = it->first;
    int nxt = next(it) == st.end() ? n + 1 : next(it)->first;
    modify(cur, -1);
    int remain = K - cur + 1;
    modify(nxt - remain, 1);
    if (nxt <= n)
      modify(nxt, -1);
    /*cerr << "test " << cur << " " << nxt << " " << remain << "\n";

    cerr << "day " << ans << "\n";
    for (auto [x, val] : st)
        cerr << "(" << x << "," << val << ")" << " ";
    cerr << "\n";*/
  }

  if (ans != -1)
    sum_ans += ans;
  if (ans == -1)
    cout << "poor monkeys\n";
  else
    cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--)
    solve();
}
