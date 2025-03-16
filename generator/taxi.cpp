#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
#define LL long long
using Unif = std::uniform_int_distribution<>;
constexpr int MN_T[] = {-1, 1, 1};
constexpr int MX_T[] = {-1, 10, 10};
constexpr long long MN_XY[] = {-1LL, 0LL, 0LL};
constexpr long long MX_XY[] = {-1LL, 10LL, 100000000000LL};
constexpr int B[] = {-1, 1, 1000000};
std::mt19937_64 rng;


constexpr int bound = 2e6;
void gen_case(char fn[], int c, int tc) {
    FILE *f = fopen(fn, "w");

	unordered_set<LL> st;

	LL N = Unif(1, 1000000)(rng);
	if (tc <= 2) N = B[tc];
	fprintf(f, "%lld\n", N);
    if (c == 2 && tc == 2) {
        for (int i = 0; i < N; i++) {
            fprintf(f, "%d", i + 1);
            if (i == N - 1) fprintf(f, "\n");
            else fprintf(f, " ");
        }
        for (int i = 0; i < N; i++) {
            fprintf(f, "%d", i + N + 1);
            if (i == N - 1) fprintf(f, "\n");
            else fprintf(f, " ");
        }
        fclose(f);
        return;

    }
	vector<int> a(2 * N);
	for (int i = 0; i < 2 * N; ++i) {
		LL gen = Unif(1, bound)(rng);
		while (st.count(gen)) {
			gen = Unif(1, bound)(rng);
		}
		st.insert(gen);
		a[i] = gen;
	}
	if (c == 1) sort(a.begin(), a.end());
	vector<int> b(N), d(N);
	for (int i = 0; i < N; ++i) {
		b[i] = a[i];
	}
	for (int i = 0; i < N; ++i) {
		d[i] = a[i + N];
	}

	// for c = 1, shuffle sorted array
	if (c == 1) {
		shuffle(b.begin(), b.end(), rng);
		shuffle(d.begin(), d.end(), rng);
	}

	for (int i = 0; i < N; ++i) {
		fprintf(f, "%d", b[i]);
		if (i == N - 1) fprintf(f, "\n");
		else fprintf(f, " ");
	}
	for (int i = 0; i < N; ++i) {
		fprintf(f, "%d", d[i]);
		if (i == N - 1) fprintf(f, "\n");
		else fprintf(f, " ");
	}
	fclose(f);

	/* For c = 1, ensure that b_i < d_i.
	 * For c = 2, generate numbers randomly.
     * Use an unordered_set to check for duplicate values, as duplicates are not allowed in this problem.
     * For each subtask, there are 5 testcases and ensure at least one test case with N = 1 and one with N = 10^6.
	 * 
	 */

		
	
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("./test2 seed test");
        assert(0);
    }

    int s = atoi(argv[1]);
    int c = atoi(argv[2]);
    rng = std::mt19937_64(s);

    char f[40];
    for (int i=1; i<=5; i++) {
        sprintf(f, "%d_%02d.in", c, i);
        gen_case(f, c, i);
    }
}


