#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>

int subtask(int argc, char **argv) {
   for (int i = 0; i + 1 < argc; i++) {
      if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

constexpr int MIN_M = 1;
constexpr int MAX_M = 1'000'000;
constexpr int MIN_C = 1;
constexpr int MAX_C = 2'000'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int m = inf.readInt(MIN_M, MAX_M, "m");
    inf.readChar('\n');

    int mxt = MIN_C, mnp = MAX_C;

    std::set<int> visit;
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(MIN_C, MAX_C, "t_" + std::to_string(i));
        if (i < m) inf.readSpace();
        else inf.readChar('\n');
        ensuref(visit.insert(x).second, "duplicate coordinates");
        mxt = std::max(mxt, x);
    }
    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(MIN_C, MAX_C, "p_" + std::to_string(i));
        if (i < m) inf.readSpace();
        else inf.readChar('\n');
        ensuref(visit.insert(x).second, "duplicate coordinates");
        mnp = std::min(mnp, x);
    }
    inf.readEof();

    if (s == 1)
        ensuref(mxt < mnp, "max t >= min p in subtask 1");
    return 0;
}
