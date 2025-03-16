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

constexpr int MIN_N = 2;
constexpr int MAX_N[] = {100, 20, 100, 100};
constexpr int MIN_L[] = {1, 5, 1, 1};
constexpr int MAX_L[] = {5'000, 5, 500, 5'000};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
   
    pattern number("[1-9][0-9]{" + std::to_string(MIN_L[s] - 1) + "," + std::to_string(MAX_L[s] - 1) + "}");

    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readChar('\n');
   
    std::set<std::string> visit;
    for (int i = 1; i <= n; ++i) {
        auto a = inf.readWord(number, "a_" + std::to_string(i));
        if (i < n) inf.readSpace();
        else inf.readChar('\n');
        ensuref(visit.insert(a).second, "duplicate numbers");
    }
    inf.readEof();

    return 0;
}
