#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <numeric>
#include <cmath>
#include <iostream>

long long encode(long long x) {
    // omitted in public repo
    return x;
}
long long decode(long long x) {
    // omitted in public repo
    return x;
}

void exit_par(double par) {
    par /= 100;
    printf("%lf\n", par);
    quitp(par, "score = %.9lf", par);
}

long long query_left[2002], query_right[2002];
long long w[2002], dp[2002];
std::vector<int> sol[2002];
long long get_subset_sum(const std::vector <int> a) {
    long long res = 0;
    for (int id : a)
        res += w[id];
    return res;
}
long long get_range_MWIS(int l, int r) {
    long long res = 0;
    for (int i = l; i <= r; ++i) {
        dp[i] = w[i];
        if (i - 1 >= l)
            dp[i] = std::max(dp[i], dp[i - 1]);
        if (i - 2 >= l)
            dp[i] = std::max(dp[i], dp[i - 2] + w[i]);
        res = std::max(res, dp[i]);
    }
    return res;
}

int main(int argc, char * argv[]) {
    inf.maxFileSize = 128 * 1024 * 1024; // 128MB
    ouf.maxFileSize = 16 * 1024 * 1024; // 16MB
    ans.maxFileSize = 16 * 1024 * 1024; // 16MB
    setName("special judge for indset");
    registerTestlibCmd(argc, argv);

    int n = decode(inf.readLong()), q = decode(inf.readLong());
    for (int i = 1; i <= n; ++i)
        w[i] = decode(inf.readLong());
    for (int i = 1; i <= q; ++i) {
        query_left[i] = decode(inf.readLong());
        query_right[i] = decode(inf.readLong());
    }

    for (int i = 1; i <= q; ++i) {
        int m = ouf.readInt(1, 2000);
        for (int j = 1; j <= m; ++j) {
            sol[i].push_back(ouf.readInt(query_left[i], query_right[i])); 
        }
    }
    ouf.readWord("Accepted:");
    long long Q_init = ouf.readLong();
    long long Q_query = ouf.readLong();

    Q_init = decode(Q_init);
    Q_query = decode(Q_query);

    for (int i = 1; i <= q; ++i) {
        std::sort(begin(sol[i]), end(sol[i]));
        for (int j = 1; j < (int)sol[i].size(); ++j) 
            if (sol[i][j] - sol[i][j - 1] <= 1)
                quitf(_wa, "Not a independent set");
        long long pans = get_subset_sum(sol[i]);
        long long jans = get_range_MWIS(query_left[i], query_right[i]);
        if (pans != jans)
            quitf(_wa, "Not maximum weight");
    }

    int W_init, W_query;
    if (Q_init <= 3)
        W_init = 100;
    else if (Q_init <= 10)
        W_init = 100 - 7 * (Q_init - 3);
    else if (Q_init <= 20)
        W_init = 50 - 4 * (Q_init - 10);
    else
        W_init = 0;

    if (Q_query <= 1)
        W_query = 100;
    else if (Q_query <= 10)
        W_query = 100 - 10 * (Q_query - 1);
    else
        W_query = 0;

    if (W_init == 100 && W_query == 100)
        quitf(_ok, "correct");
    else if (W_init == 0 || W_query == 0)
        quitf(_wa, "wa");
    else
        exit_par(1.0 * W_init * W_query / 100);
}
