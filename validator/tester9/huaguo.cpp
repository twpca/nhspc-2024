#include "testlib.h"
#include <bits/stdc++.h>

const int SUBTASKS = 5;
const int MAX_N[SUBTASKS + 1] = {1'000'000, 100, 100, 1000, 100000, 1'000'000};
const int MAX_K[SUBTASKS + 1] = {1'000'000'000, 100, 100, 1000, 100000, 1'000'000'000};
const int MAX_A[SUBTASKS + 1] = {1'000'000'000, 100, 100, 1000, 100000, 1'000'000'000};
const int MAX_ANS[SUBTASKS + 1] = {-1, -1, -1, 10000, 100000, -1};
const int MAX_SUM_ANS[SUBTASKS + 1] = {-1, -1, -1, -1, 100000, -1};
const int YES[SUBTASKS + 1] = {0, 1, 1, 0, 0, 0};

int sum_n;

using ll = __int128;
void extgcd(ll x, ll y, ll &g, ll &a, ll &b) {
	if (y == 0) g = x, a = 1, b = 0;
	else extgcd(y, x % y, g, b, a), b -= (x / y) * a;
}
ll iceil(ll a, ll b){
	return a / b + (a % b && (a < 0) ^ (b > 0));
}

long long calc(int n, int K, ll min_a, ll max_a, ll sum_a) {
    K %= n;
    ll g = std::gcd(n, K);
    ll p, t;
    extgcd(n, K, g, p, t);
    t = -t;
    p *= sum_a / g;
    t *= sum_a / g;
    
    ll diff_p = K / g;
    ll diff_t = n / g;
    ll add = iceil(max_a - p, diff_p);
    p += add * diff_p;
    t += add * diff_t;

    ll tmp = iceil((p - t - min_a), ((n - K) / g));
    if (tmp > 0) t += tmp * (n / g), p += tmp * (K / g);
    return t;
}

long long sum_ans = 0;
void solve(int subtask) {

    int n = inf.readInt(2, MAX_N[subtask], "n");
    inf.readSpace();
    int K = inf.readInt(1, MAX_K[subtask], "k");
    inf.readEoln();

    sum_n += n;
    ensuref(sum_n <= MAX_N[subtask], "sum n too large");
    if (subtask == 1) ensuref(K == 1, "k != 1 for subtask 1");
    if (subtask == 2) ensuref(K == n - 1, "k != n - 1 for subtask 2");
    
    std::vector<int> a(n + 1);
    long long sum_a = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = inf.readInt(0, MAX_A[subtask], "a_i");
        sum_a += a[i];
        if (i < n) inf.readSpace();
        else inf.readEoln();
    }
    for (int i = 1; i < n; i++)
        ensuref(a[i] <= a[i + 1], "a[i] > a[i + 1]");
    ensuref(a[1] < a[n], "a_1 = a_n");

    int g = std::gcd(n, K);
    ensuref(sum_a % g == 0 || YES[subtask] != 1, "no solution");

    if (K % n != 0 && sum_a % g == 0) {
        long long ans = calc(n, K, a[1], a[n], sum_a);
        if (MAX_SUM_ANS[subtask] != -1) {
            sum_ans += ans;
            ensuref(sum_ans <= MAX_SUM_ANS[subtask], "sum answer too large");
        }
        if (MAX_ANS[subtask] != -1) ensuref(ans <= MAX_ANS[subtask], "answer too large");
    }
    
}


int get_subtask(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp("--testcase", argv[i - 1])) {
            int subtask = atoi(argv[i]);
            assert(0 <= subtask && subtask <= SUBTASKS);
            return subtask;
        }
    }
    assert(0);
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int subtask = get_subtask(argc, argv);

    int T = inf.readInt(1, 500000, "T");
    inf.readEoln();
    while (T--) solve(subtask);
    inf.readEof();

    return 0;
}
