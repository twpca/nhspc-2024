#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 10'000'000;
const int mod = 1'000'000'007;

ll fast_pow(ll val, int n) {
    if (n == 0) return 1;
    if (n & 1) return val * fast_pow(val, n - 1) % mod;
    return fast_pow(val * val % mod, n / 2);
}

ll mod_inv(ll val) {
    assert(val % mod != 0);
    return fast_pow(val, mod - 2);
}

void solve() {
    int t;
    cin >> t;

    vector<int> n(t + 1);
    for (int &i : n)
        cin >> i;

    vector<ll> factorial(MAX_N + 1, 1);
    for (int i = 2; i <= MAX_N; ++i)
        factorial[i] = factorial[i - 1] * i % mod;

    ll n0_inv = mod_inv(factorial[n[0]]);
    ll ans = factorial[n[0]] * fast_pow(n0_inv, t) % mod;
    for (int i = 1; i <= t; ++i)
        ans = ans * factorial[n[i] + n[0]] % mod;

    cout << ans << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
