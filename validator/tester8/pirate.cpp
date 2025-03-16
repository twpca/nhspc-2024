#include<bits/stdc++.h>
#include "testlib.h"

using namespace std;

static constexpr int SUBTASKS = 4;
static constexpr int MIN_N[SUBTASKS + 1] = {1, 1, 1, 1, 1};
static constexpr int MAX_N[SUBTASKS + 1] = {10000, 500, 5000, 10000, 10000};
static constexpr int MIN_M[SUBTASKS + 1] = {1, 1, 1, 1, 1};
static constexpr int MAX_M[SUBTASKS + 1] = {100000, 100000, 10000, 100000, 100000};
static constexpr int MIN_Q[SUBTASKS + 1] = {1, 1, 1, 1, 1};
static constexpr int MAX_Q[SUBTASKS + 1] = {30000, 30000, 30000, 30000, 30000};

int subtask(int argc, char* argv[]) {
    using namespace std::string_literals;
    for (int i{1}; i < argc; ++i) {
        if (argv[i-1] == "--testcase"s) {
            int s{static_cast<int>(std::stoi(argv[i]))};
            assert(s <= SUBTASKS);
            return s;
        }
    }
    assert(0);
    return -1;
}

void dfs(int x, vector<vector<int>> &edge, vector<bool> &vis) {
	for(auto y: edge[x]) {
		if (vis[y]) continue;
		vis[y] = true;
		dfs(y, edge, vis);
	}
}

int main(int argc, char* argv[]) {
  
  registerValidation(argc, argv);
  const int s{subtask(argc, argv)};
//  int main() {
//  	int s = 4;
//  	freopen("4_07_autogen.in", "r", stdin);
// 	 registerValidation();
	
	int n = inf.readInt(MIN_N[s], MAX_N[s]);
	inf.readSpace();
	int m = inf.readInt(MIN_M[s], MAX_M[s]);
	inf.readSpace();
	int q = inf.readInt(MIN_Q[s], MAX_Q[s]);
	inf.readChar('\n');
	
	vector<vector<int>> edge(n);
	vector<pair<int, int>> query(q);
	map<pair<int, int>, bool> has;
	
	
	for(int k=0;k<m;k++) {
		int a = inf.readInt(1, n);
		inf.readSpace();
		int b = inf.readInt(1, n);
		inf.readChar('\n');
		ensuref(a != b, "edge has same endpoint");
		a--; b--;
		if (a > b) swap(a, b);
		ensuref(!has[make_pair(a, b)], "having same edge");
		has[make_pair(a, b)] = true;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	
	vector<bool> vis(n, false);
	vis[0] = true;
	dfs(0, edge, vis);
	for(int k=0;k<n;k++) {
		ensuref(vis[k], "graph is not connected");
	}
	
	for(int k=0;k<q;k++) {
		int a = inf.readInt(1, n);
		inf.readSpace();
		int b = inf.readInt(1, n);
		inf.readChar('\n');
		a--; b--;
		query.push_back(make_pair(a, b));
	}
	
	inf.readEof();
}