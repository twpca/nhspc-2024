#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, K;
  cin >> n >> K;

  int max_a = 0, min_a = INT_MAX, total_a = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    max_a = max(max_a, a);
    min_a = min(min_a, a);
    total_a += a;
  }
  cout << total_a - min_a * n << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--)
    solve();
}
