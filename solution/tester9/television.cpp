#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1'000'000'007;
const int MAXN = 10'000'005;
ll dp[MAXN];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  int n0;
  cin >> n0;

  dp[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    dp[i] = dp[i - 1] * (n0 + i) % MOD;
  }

  ll ans = 1;
  for (int i = 1; i <= n0; i++) {
    ans = ans * i % MOD;
  }

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    ans = ans * dp[a] % MOD;
  }
  cout << ans << "\n";
}
