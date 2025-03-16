#include <vector>
#include <cassert>
#include <algorithm>

bool compare_subsets(const std::vector<int>& a, const std::vector<int>& b);

int n;

bool prefix_sol[2002][2002];
int ord[2][2002], tmp[2002], rk[2][2002];

bool cmp(int x, int y) {
	if (x < y) {
		std::vector <int> veca, vecb;
		for (int i = x; i < y; ++i) {
			if ((i - x) % 2 == 0)
				veca.push_back(i);
			else
				vecb.push_back(i);
		}
		return compare_subsets(veca, vecb);
	} else {
		std::vector <int> veca, vecb;
		for (int i = y; i < x; ++i) {
			if ((i - y) % 2 == 0)
				veca.push_back(i);
			else
				vecb.push_back(i);
		}
		return compare_subsets(vecb, veca);
	}
}

void dc(int id, int l, int r) {
	if (r - l == 1)
		return;
	int m = l + r >> 1;
	dc(id, l, m);
	dc(id, m, r);
	for (int i = l, j = m, ptr = l; i < m || j < r; )
		if (j == r || (i < m && cmp(ord[id][i], ord[id][j])))
			tmp[ptr++] = ord[id][i++];
		else
			tmp[ptr++] = ord[id][j++];
	for (int i = l; i < r; ++i)
		ord[id][i] = tmp[i];
}

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
	for (int x = 0; x < 2; ++x) {
		int sz = 0;
		for (int i = x + 1; i <= n; i += 2) {
			ord[x][sz] = i;
			sz += 1;
		}
		dc(x, 0, sz);
		for (int i = 0; i < sz; ++i)
			rk[x][ord[x][i]] = i;
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
			if ((i - l) % 2 == 0 && (flip == -1 || rk[(l & 1) ^ 1][flip] > rk[(l & 1) ^ 1][i]))
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