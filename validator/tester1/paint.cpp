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

constexpr int MIN_S = 1;
constexpr int MAX_S[] = {1'000'000, 1'000'000, 1'000, 1'000'000};
constexpr int MIN_D = 1;
constexpr int MAX_D[] = {7, 2, 3, 7};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    std::string str = inf.readWord("[a-zA-Z]{" + std::to_string(MIN_S) + "," + std::to_string(MAX_S[s]) + "}", "S");
    inf.readChar('\n');
    inf.readEof();

    std::set<char> distinct(str.begin(), str.end());
    ensuref(MIN_D <= distinct.size() && distinct.size() <= MAX_D[s], "distinct(S) ouf of range");

    return 0;
}
