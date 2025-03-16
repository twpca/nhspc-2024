#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 10'000'000;
const int mod = 1'000'000'007;

void solve() {
    int t;
    cin >> t;

    vector<int> n(t + 1);
    for (int &i : n)
        cin >> i;

    vector<ll> factorial(2 * MAX_N + 1, 1);
    for (int i = n[0] + 1; i <= 2 * MAX_N; ++i)
        factorial[i] = factorial[i - 1] * i % mod;

    ll ans = 1;
    for (int i = 2; i <= n[0]; ++i)
        ans = ans * i % mod;

    for (int i = 1; i <= t; ++i)
        ans = ans * factorial[n[i] + n[0]] % mod;

    cout << ans << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
