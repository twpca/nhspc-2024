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
	
//	freopen("4_07_autogen.in", "r", stdin);
//	freopen("4_07_autogen.out", "w", stdout);
	
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	vector<vector<int>> dis(n, vector<int>(n));
	vector<vector<int>> edge(n, vector<int>());
	
	
	for(int k=0;k<m;k++) {                     
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	
	for(int k=0;k<n;k++) {
		bfs(k, dis[k], edge);
	}
	
	for(int t=0;t<q;t++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		printf("%d", dis[a][b]);
		printf("%c", t < q - 1? ' ': '\n');
	}
}