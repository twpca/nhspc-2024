#include "testlib.h"
#include <cassert>

constexpr int MIN_T = 0;
constexpr int MAX_T[] = {10, 0, 1, 2, 1'000'000};
constexpr int MIN_N = 1;
constexpr int MAX_N = 10'000'000;

int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}

int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int t = inf.readInt(MIN_T, MAX_T[s], "t");
    inf.readChar('\n');
    inf.readInts(t + 1, MIN_N, MAX_N);
    inf.readChar('\n');
    inf.readEof();
}
