#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n, K;
  cin >> n >> K;
  int g = gcd(n, K);

  vector<int> a(n);
  ll sum_a = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum_a += a[i];
  }
  if (K == 0 || sum_a % g) {
    cout << "poor monkeys\n";
    return;
  }

  int ans = 0;
  while (a[0] != a[n - 1]) {
    if (ans >= 10000) {
      cout << "poor monkeys\n";
      return;
    }
    for (int i = 0; i < n; i++)
      a[i] += K / n + (i < K % n);
    sort(a.begin(), a.end());
    ans++;
  }
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
