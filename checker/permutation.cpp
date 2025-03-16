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
    printf("%lf\n", par);
    quitp(par, "score = %.9lf", par);
}

int main(int argc, char * argv[]) {
    inf.maxFileSize = 128 * 1024 * 1024; // 128MB
    ouf.maxFileSize = 16 * 1024 * 1024; // 16MB
    ans.maxFileSize = 16 * 1024 * 1024; // 16MB
    setName("special judge for permutation");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(), k = inf.readInt();
    std::vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i)
        p[i] = decode(inf.readLong());
    std::vector<int> query(k + 1);
    for (int i = 1; i <= k; ++i)
        query[i] = decode(inf.readLong());

    std::vector<int> sol(k + 1);
    for (int i = 1; i <= k; ++i) {
        sol[i] = ouf.readInt(1, n);
        if (sol[i] != p[query[i]])
            quitf(_wa, "wa");
    }
    ouf.readWord("Accepted:");
    long long Q = decode(ouf.readLong());

    double W;
    if (Q <= 9)
        W = 1;
    else if (Q <= 500)
        W = 3 / std::sqrt(Q);
    else
        W = 0;

    if (W == 1)
        quitf(_ok, "correct");
    else if (W == 0)
        quitf(_wa, "wa");
    else
        exit_par(W);
}
