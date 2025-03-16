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

  auto add = [&](int l, int r, ll v) {
    // cerr << "add [" << l << ',' << r << ") += " << v << "\n";
    if (l <= n) {
      st[l] += v;
      if (st[l] == 0)
        st.erase(l);
    }
    if (r <= n) {
      st[r] -= v;
      if (st[r] == 0)
        st.erase(r);
    }
  };

  const ll MAX = 1LL << 60;
  ll ans = 0;
  while (int(st.size()) >= 2) {
    auto it = get_iter(K);
    auto [cur, cur_diff] = *it;
    auto [pre, pre_diff] = cur > 1 && cur_diff == 1 ? *prev(it) : *it;
    if (next(it) != st.end() && next(it)->second == 1)
      it++;
    auto [nxt, nxt_diff] =
        next(it) == st.end() ? make_pair(n + 1, 0LL) : (pair<int, ll>)*next(it);
    auto [rgt, rgt_diff] =
        it->first <= K ? make_pair(nxt, nxt_diff) : (pair<int, ll>)*it;

    // a[K]-1:[pre, cur)
    // a[K]:  [cur, rgt)
    // a[K]+1:[rgt, nxt)

    if (pre == 1 && nxt == n + 1) {
      ll tmp = cur - pre;
      if (rgt < nxt)
        tmp += rgt - pre;
      // cerr << "QQ " << tmp << "\n";
      assert(tmp % g == 0);
      // K * x - n * y = tmp
      auto [x, y] = extgcd(K, n);
      x *= tmp / g;
      y *= tmp / g;
      y = -y;
      assert(K * x - n * y == tmp);
      /*if (y < 0) {
          ll t = iceil(-y, K / g);
          y += t * K / g;
          x += t * n / g;
      }
      else {
          ll t = ifloor(y, K / g);
          y -= t * K / g;
          x -= t * n / g;
      }*/
      // cerr << "test " << x << " " << y << " : " << K * x - n * y << "\n";
      assert(K * x - n * y == tmp);
      ans += x;
      break;
    }

    auto get_pre_increase = [&](ll time) {
      time *= (K - pre + 1);
      ll tmp = 0;
      if (time >= cur - pre) {
        if (pre < cur)
          tmp++;
        time -= cur - pre;
      } else
        time = 0;
      if (time >= rgt - pre) {
        tmp++;
        time -= rgt - pre;
      } else
        time = 0;
      tmp += time / (nxt - pre);
      return tmp;
    };
    auto get_nxt_increase = [&](ll time) { // nxt - 1
      time *= (K - pre + 1);
      ll tmp = 0;
      if (time >= cur - pre)
        time -= cur - pre;
      else
        time = 0;
      if (time > 0 && rgt == nxt)
        tmp++;
      if (time >= rgt - pre)
        time -= rgt - pre;
      else
        time = 0;
      tmp += (time + nxt - pre - 1) / (nxt - pre);
      return tmp;
    };

    ll l = 0, r = 1LL << 35;
    while (l + 1 < r) {
      ll mid = (l + r) / 2;

      ll tmp = get_pre_increase(mid);
      if (pre > 1 && mid >= pre_diff + tmp) {
        r = mid;
        continue;
      }

      tmp = get_nxt_increase(mid);
      if (nxt <= n && tmp >= nxt_diff) {
        r = mid;
        continue;
      }
      l = mid;
    }

    ll next_event = r;
    /*cerr << "check " << next_event << " : " << pre_diff << " " <<
       get_pre_increase(next_event)
        << " " << get_nxt_increase(next_event) << " " << nxt_diff << "\n";*/

    ans += next_event;

    add(1, pre, next_event);

    next_event *= (K - pre + 1);
    if (next_event < cur - pre) {
      add(cur - next_event, cur, 1);
    } else if (next_event < cur - pre + rgt - pre) {
      add(pre, cur, 1);
      add(rgt - (next_event - (cur - pre)), rgt, 1);
    } else {
      add(pre, cur, 1);
      add(pre, rgt, 1);
      ll increase = (next_event - (cur - pre) - (rgt - pre)) / (nxt - pre);
      ll remain = (next_event - (cur - pre) - (rgt - pre)) % (nxt - pre);
      add(pre, nxt, increase);
      add(nxt - remain, nxt, 1);
    }

    /*cerr << "day " << ans << " " << pre << " " << cur << " " << rgt << " " <<
    nxt << " | " << K << "\n"; for (auto [x, v] : st) cerr << '(' << x << ',' <<
    v << ')'; cerr << "\n";*/
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
