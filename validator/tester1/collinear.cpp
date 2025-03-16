#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cstring>
#include <set>

int subtask(int argc, char **argv) {
   for (int i = 0; i + 1 < argc; i++) {
      if (!strcmp(argv[i], "--testcase")) {
            return atoi(argv[i + 1]);
      }
   }
   abort();
}

constexpr long long int MIN_N = 1;
constexpr long long int MAX_N[] = {100'000, 100'000, 300, 100'000};
constexpr long long int MIN_C = -1'000'000'000;
constexpr long long int MAX_C = 1'000'000'000;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    int n = inf.readInt(MIN_N, MAX_N[s], "n");
    inf.readSpace();
    if (s == 1) inf.readInt(n, n, "k");
    else inf.readInt((n + 3) / 4, n, "k");
    inf.readChar('\n');

    std::set<std::pair<int, int>> visit;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(MIN_C, MAX_C, "x_" + std::to_string(i));
        inf.readSpace();
        int y = inf.readInt(MIN_C, MAX_C, "y_" + std::to_string(i));
        inf.readChar('\n');
        ensuref(visit.emplace(x, y).second, "duplicate points");
    }
    inf.readEof();
    return 0;
}
