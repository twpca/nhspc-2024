#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
  int n, K;
  cin >> n >> K;
  K %= n;
  ll g = gcd(n, K);

  ll max_a = 0, min_a = LLONG_MAX, total_a = 0;
  for (int i = 0; i < n; i++) {
    long long a;
    cin >> a;
    max_a = max(max_a, (ll)a);
    min_a = min(min_a, (ll)a);
    total_a += a;
  }

  if (K == 0 || total_a % g) {
    cout << "poor monkeys\n";
    return;
  }

  ll t = max(max_a, (total_a - K * min_a + n - K - 1) / (n - K));
  while ((n * t - total_a) % K != 0)
    t++;
  ll ans = (n * t - total_a) / K;
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
