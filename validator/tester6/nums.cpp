#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int SUBTASKS = 3;
constexpr int MN_N = 2;
constexpr int MX_N[SUBTASKS+1] = {100, 20, 100, 100};
constexpr int MN_L[SUBTASKS+1] = {1, 5, 1, 1};
constexpr int MX_L[SUBTASKS+1] = {5000, 5, 500, 5000};
int n;
string A[105];

int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            int subtask = atoi(argv[i]);
            assert(0 <= subtask && subtask <= SUBTASKS);
            return subtask;
        }
    }
    assert(0);
    return -1;
}

void check_dup() {
    sort(A+1, A+n+1);
    REP(i,2,n) ensuref(A[i] != A[i-1], "should not have duplicate numbers");
}

int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    string pattern_max = format("[0-9]{1, %d}", MX_L[0]);
    n = inf.readInt(MN_N, MX_N[s], "n"); inf.readChar('\n');
    for (int i=1; i<=n; i++) {
        string a = inf.readToken(pattern_max);
        A[i] = a;
        if (i < n) {
            inf.readChar(' ');
        } else {
            inf.readChar('\n');
        }

        // check a is a valid number
        int len = (int)a.length();
        ensuref(MN_L[s] <= len, "length a[%d] should >= %d", i, MN_L[s]);
        ensuref(len <= MX_L[s], "length a[%d] should <= %d", i, MX_L[s]);
        ensuref(a[0]!='0' || len==1, "a[%d] should not have leading zeros", i);
    }
    inf.readEof();
    check_dup();
    return 0;
}
