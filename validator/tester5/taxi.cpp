#include<bits/stdc++.h>
#include<cstring>
#include<cassert>
#include "../yzkkai/testlib.h"

constexpr int bound = 2e6;
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
constexpr long long L = 1, R = 2e6;
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
	
    int N = inf.readInt(1, 1000000);
    inf.readChar('\n');
	std::unordered_set<long long> st;	
	long long mx = 0, mn = 1e9;

	// t_i
	for (int i = 0; i < N; i++) {
		long long x = inf.readLong(L, R);
		ensuref(!st.count(x), "Not allow duplicate values");
		st.insert(x);
		if (mx < x) mx = x;
		if (i == N - 1) inf.readChar('\n');
		else inf.readSpace();
	}

	// p_i
	for (int i = 0; i < N; i++) {
		long long x = inf.readLong(L, R);
		ensuref(!st.count(x), "Not allow duplicate values");
		st.insert(x);
		if (mn > x) mn = x;
		if (i == N - 1) inf.readChar('\n');
		else inf.readSpace();
	}

	if (s == 1) ensuref(mx < mn, "ti < pi in subtask1");
    inf.readEof();

    /* for c = 1, check max(t_i) < min(p_i)
	 * Not allow duplicate values
	 * 1 <= N <= 10^6, 1 <= t_i, p_i <= 2 * 10^6
   	*/
}


