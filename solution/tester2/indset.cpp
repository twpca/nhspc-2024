#include <vector>
#include <cassert>

bool compare_subsets(const std::vector<int>& a, const std::vector<int>& b);

int n;

bool prefix_sol[2002][2002], monotone_tag[2002][2002];

void init(int _n) {
	n = _n;
	prefix_sol[1][1] = true;
	for (int i = 2; i <= n; ++i) {
		std::vector <int> from1, from2;
		for (int j = 1; j <= i - 1; ++j)
			if (prefix_sol[i - 1][j])
				from1.push_back(j);
		for (int j = 1; j <= i - 2; ++j)
			if (prefix_sol[i - 2][j])
				from2.push_back(j);
		from2.push_back(i);
		if (compare_subsets(from1, from2))
			swap(from1, from2);
		for (int j : from1)
			prefix_sol[i][j] = true;
	}
	std::vector <int> stk[2];
	for (int i = n; i > 0; --i) {
		int id = i % 2;
		while (!stk[id].empty()) {
			int lst = stk[id].back();
			std::vector <int> veca, vecb;
			for (int j = i; j < lst; ++j) {
				if ((j - i) % 2 == 0)
					veca.push_back(j);
				else
					vecb.push_back(j);
			}
			if (compare_subsets(vecb, veca))
				break;
			stk[id].pop_back();
		}
		stk[id].push_back(i);
		for (int j : stk[id])
			monotone_tag[i][j] = true;
	}
}

std::vector<int> range_MWIS_query(int l, int r) {
	std::vector <int> sol;
	if (l == r) {
		sol.push_back(l);
	} else if (l + 1 == r) {
		std::vector <int> sol1, sol2;
		sol1.push_back(l);
		sol2.push_back(r);
		if (compare_subsets(sol1, sol2))
			sol = sol2;
		else
			sol = sol1;
	} else if (prefix_sol[r][l]) {
		for (int i = l; i <= r; ++i)
			if (prefix_sol[r][i])
				sol.push_back(i);
	} else if (prefix_sol[r][l + 1]) {
		std::vector <int> sol1, sol2;
		int flip = -1, gap = r;
		for (int i = l; i <= r; ++i) {
			if (i + 1 <= r && !prefix_sol[r][i] && !prefix_sol[r][i + 1]) {
				gap = i;
				break;
			}
			if (monotone_tag[l][i])
				flip = i;
		}
		for (int i = l; i <= gap; ++i)
			if (!prefix_sol[r][i])
				sol1.push_back(i);
		for (int i = gap + 1; i <= r; ++i)
			if (prefix_sol[r][i])
				sol1.push_back(i);
		for (int i = l; i < flip; ++i)
			if (!prefix_sol[r][i])
				sol2.push_back(i);
		for (int i = flip; i <= r; ++i)
			if (prefix_sol[r][i])
				sol2.push_back(i);
		if (compare_subsets(sol1, sol2))
			sol = sol2;
		else
			sol = sol1;
	} else if (prefix_sol[r][l + 2]) {
		for (int i = l; i <= r; ++i)
			if (prefix_sol[r][i])
				sol.push_back(i);
		sol.push_back(l);
	} else {
		assert(false);
	}
	return sol;
}