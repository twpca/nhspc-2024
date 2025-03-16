#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>

long long encode(long long x) {
    // omitted in public repo
    return x;
}
long long decode(long long x) {
    // omitted in public repo
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

constexpr long long int MIN_N = 1;
constexpr long long int MAX_N[] = {1'000, 2, 1'000};
constexpr long long int MIN_K = 1;
constexpr long long int MAX_K = 1'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readSpace();
    int k = inf.readInt(MIN_K, MAX_K, "k");
    inf.readChar('\n');

    std::set<int> visit;
    for (int i = 1; i <= n; ++i) {
        long long p = inf.readLong(0LL, 1152921504606846975LL, "p_" + std::to_string(i));
        if (i < n) inf.readSpace();
        else inf.readChar('\n');
        p = decode(p);
        ensuref(1 <= p && p <= n, "number not between [1, n]: %lld", p);
        ensuref(visit.insert(p).second, "not a permutation");
    }
    for (int i = 1; i <= k; ++i) {
        long long p = inf.readLong(0LL, 1152921504606846975LL, "a_" + std::to_string(i));
        if (i < k) inf.readSpace();
        else inf.readChar('\n');
        p = decode(p);
        ensuref(1 <= p && p <= n, "number not between [1, n]: %lld", p);
    }
    inf.readEof();
    return 0;
}
