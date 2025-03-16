#include <vector>
#include <cassert>
#include <algorithm>

bool compare_subsets(const std::vector<int>& a, const std::vector<int>& b);

int n;

std::vector <int> sol[2002];

void init(int _n) {
	n = _n;
	sol[1].push_back(1);
	for (int i = 2; i <= n; ++i) {
		std::vector <int> from1 = sol[i - 1], from2 = sol[i - 2];
		from2.push_back(i);
		if (compare_subsets(from1, from2))
			swap(from1, from2);
		sol[i] = from1;
	}
}

std::vector<int> range_MWIS_query(int l, int r) {
	return sol[r];
}