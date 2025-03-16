#include "testlib.h"

const int MAXN = 2000;
const int MAXQ = 2000;
const int MAXC = 1'000'000'000;
long long encode(long long x) {
    // omitted in public repo
    return x;
}
long long decode(long long x) {
    // omitted in public repo
    return x;
}

long long read_and_decode(long long l, long long r) {
    long long x = decode(inf.readLong());
    ensure(l <= x && x <= r);
    return x;
}

int subtask(int argc, char **argv) {
   for (int i = 0; i + 1 < argc; i++) {
      if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int task = subtask(argc, argv);

    int n = read_and_decode(1, MAXN);
    inf.readSpace();
    int q = read_and_decode(1, MAXQ);
    inf.readEoln();

    std::vector <long long> w(n + 1);
    for (int i = 1; i <= n; ++i) {
        w[i] = read_and_decode(1, MAXC);
        if (i + 1 <= n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    std::vector <long long> dp(n + 1), lst(n + 1), cnt(n + 1);
    dp[1] = w[1];
    cnt[0] = cnt[1] = 1;
    lst[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1];
        cnt[i] = cnt[i - 1];
        lst[i] = 1;
        if (dp[i] < dp[i - 2] + w[i]) {
            dp[i] = dp[i - 2] + w[i];
            cnt[i] = cnt[i - 2];
            lst[i] = 2;
        } else if (dp[i] == dp[i - 2] + w[i])
            cnt[i] = std::min<long long>(cnt[i] + cnt[i - 2], 2);
    }

    for (int i = 1; i <= q; ++i) {
        long long l = read_and_decode(1, n);
        inf.readSpace();
        long long r = read_and_decode(l, n);
        inf.readEoln();

        if (task == 1)
            ensure(l == 1);
        if (task == 2) {
            ensure(cnt[r] == 1);
            for (int j = r; j > 0; j -= lst[j])
                if (lst[j] == 2)
                    ensure(j != l + 1);
        }
    }

    inf.readEof();
}
