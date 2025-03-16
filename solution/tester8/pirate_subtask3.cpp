#include<bits/stdc++.h>

using namespace std;

const int INF = 1000000;

void bfs(int x, vector<int> &dis, vector<vector<int>> &edge) {
	queue<int> Q;
	Q.push(x);
	while (!Q.empty()) {
		int y = Q.front();
		Q.pop();
		for(auto z: edge[y]) {
			if (dis[z] != 0 || z == x) continue;
			dis[z] = dis[y] + 1;
			Q.push(z);
		}
	}
}

int main () {
	
//	freopen("input_4-7.txt", "r", stdin);
//	freopen("output_4-7_test3.txt", "w", stdout);
	
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	vector<vector<int>> edge(n, vector<int>());
	
	
	
	for(int k=0;k<m;k++) {                     
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	
//	for(int k=0;k<n;k++) {
//		bfs(k, dis[k], edge);
//	}
	
	vector<pair<int, int>> query;
	vector<int> cover(n, 0);
	
	int coverNum = 0;
	
	for(int t=0;t<q;t++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		query.push_back(make_pair(a, b));
		if (cover[a] == 0 && cover[b] == 0) {
			cover[a] = ++coverNum;
			cover[b] = ++coverNum;
		}
	}
	
	vector<vector<int>> dis(coverNum, vector<int>(n));
	
	for(int k=0;k<n;k++) {
		if (cover[k] > 0) {
			bfs(k, dis[cover[k] - 1], edge);
		}
	}
	
	for(int t=0;t<q;t++) {
		int a = query[t].first, b = query[t].second;
		if (cover[a] == 0) swap(a, b);
		printf("%d", dis[cover[a] - 1][b]);
		printf("%c", t < q - 1? ' ': '\n');
	}
	
}