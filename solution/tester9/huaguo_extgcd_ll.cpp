#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

pll extgcd(ll a, ll b) {
  if (b == 0)
    return pll(1, 0);
  ll p = a / b;
  pll q = extgcd(b, a % b);
  return pll(q.second, q.first - q.second * p);
}
ll iceil(ll a, ll b) { return a / b + (a % b && (a < 0) ^ (b > 0)); }

void solve() {
  int n, K;
  cin >> n >> K;
  K %= n;
  ll g = gcd(n, K);

  ll max_a = 0, min_a = LLONG_MAX, total_a = 0;
  for (int i = 0; i < n; i++) {
    ll a;
    cin >> a;
    max_a = max(max_a, a);
    min_a = min(min_a, a);
    total_a += a;
  }

  if (K == 0 || total_a % g) {
    cout << "poor monkeys\n";
    return;
  }

  auto [p, t] = extgcd(n, K);
  t = -t;
  p *= total_a / g;
  t *= total_a / g;

  ll diff_p = K / g;
  ll diff_t = n / g;
  ll add = iceil(max_a - p, diff_p);
  p += add * diff_p;
  t += add * diff_t;

  ll tmp = iceil((p - t - min_a), ((n - K) / g));
  if (tmp > 0)
    t += tmp * (n / g), p += tmp * (K / g);
  cout << t << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--)
    solve();
}
