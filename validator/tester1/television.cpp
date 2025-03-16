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

constexpr int MIN_T = 0;
constexpr int MAX_T[] = {1'000'000, 0, 1, 2, 1'000'000};
constexpr int MIN_N = 1;
constexpr int MAX_N = 10'000'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int t = inf.readInt(MIN_T, MAX_T[s], "t");
    inf.readChar('\n');

    for (int i = 0; i <= t; ++i) {
        inf.readInt(MIN_N, MAX_N, "n_" + std::to_string(i));
        if (i < t) inf.readSpace();
        else inf.readChar('\n');
    }
    inf.readEof();

    return 0;
}
