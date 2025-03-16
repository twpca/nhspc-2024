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

ll ifloor(ll a, ll b) { return a / b - (a % b && (a < 0) ^ (b < 0)); }
ll iceil(ll a, ll b) { return a / b + (a % b && (a < 0) ^ (b > 0)); }
ll int128_abs(ll a) { return a < 0 ? -a : a; }

void solve() {
  int n, K;
  cin >> n >> K;
  K %= n;
  ll g = gcd(n, K);

  vector<ll> a(n + 1);
  a[0] = -1;
  map<int, ll> st;
  ll sum_a = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum_a += a[i];
    if (a[i] != a[i - 1])
      st[i] = a[i] - a[i - 1];
  }

  if (K == 0 || sum_a % g) {
    cout << "poor monkeys\n";
    return;
  }

  auto get_iter = [&](int x) -> map<int, ll>::iterator {
    auto it = st.upper_bound(x);
    return prev(it);
  };

  const ll MAX = 1LL << 60;
  ll ans = 0;
  while (int(st.size()) >= 2) {
    auto it = get_iter(K);
    auto [cur, cur_diff] = *it;
    auto [nxt, nxt_diff] =
        next(it) == st.end() ? make_pair(n + 1, 0LL) : (pair<int, ll>)*next(it);

    ll len = nxt - cur;
    ll cnt = K - cur + 1;

    ll next_event = nxt <= n ? nxt_diff * len / cnt : MAX;

    if (cur > 1 && cnt < len) {
      ll tmp = (len * cur_diff - len) / (len - cnt);
      while (tmp < cur_diff + tmp * cnt / len)
        tmp++;
      next_event = min(next_event, tmp);
    }

    ans += next_event;
    st[1] += next_event;
    st[cur] -= next_event;
    ll add = next_event * cnt / len;
    ll remain = next_event * cnt % len;
    st[cur] += add;
    if (nxt - remain <= n) {
      st[nxt - remain] += 1;
      if (nxt <= n)
        st[nxt] -= 1;
    }
    if (nxt <= n)
      st[nxt] -= add;
    if (st[cur] == 0)
      st.erase(cur);
    if (nxt <= n && st[nxt] == 0)
      st.erase(nxt);
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
