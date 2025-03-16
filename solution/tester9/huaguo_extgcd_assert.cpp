#include <bits/stdc++.h>
using namespace std;
using ll = __int128;
using pll = pair<ll, ll>;

pll extgcd(ll a, ll b) {
  if (b == 0)
    return pll(1, 0);
  ll p = a / b;
  pll q = extgcd(b, a % b);
  return pll(q.second, q.first - q.second * p);
}

ll ifloor(ll a, ll b) { return a / b - (a % b && (a < 0) ^ (b < 0)); }
ll iceil(ll a, ll b) { return a / b + (a % b && (a < 0) ^ (b > 0)); }
ll int128_abs(ll a) { return a < 0 ? -a : a; }

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

  auto [p, t] = extgcd(n, K);
  t = -t;
  // debug(n, K, g, '|', p, t, n / g, K / g);
  assert(int128_abs(p) <= K / g);
  assert(int128_abs(t) <= n / g);
  assert(n * p - K * t == g);
  p *= total_a / g;
  t *= total_a / g;
  assert(n * p - K * t == total_a);

  ll diff_p = K / g;
  ll diff_t = n / g;
  ll add = max(iceil(max_a - p, diff_p), iceil(-t, diff_t));
  p += add * diff_p;
  t += add * diff_t;

  assert(n * p - K * t == total_a);
  assert(p >= max_a);
  assert(t >= 0);
  assert(p - diff_p < max_a || t - diff_t < 0);

  // debug("test", p, t, diff_p, diff_t, min_a);
  ll tmp = iceil((p - t - min_a), ((n - K) / g));
  // debug("tmp", tmp);
  if (tmp > 0)
    t += tmp * (n / g), p += tmp * (K / g);
  assert(n * p - K * t == total_a);
  assert(p >= max_a);
  assert(t >= 0);
  assert(p - t <= min_a);
  // debug("test", p, t, diff_p, diff_t, min_a);
  assert((p - diff_p) - (t - diff_t) > min_a || p - diff_p < max_a ||
         t - diff_t < 0);
  cout << (long long)t << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--)
    solve();
}
