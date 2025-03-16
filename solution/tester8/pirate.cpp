#include<bits/stdc++.h>

using namespace std;

const int SZ = 1300;

unsigned seed = 1334;
mt19937 g(seed);

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
	
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	
	int sz = min(n, SZ);
	
	vector<vector<int>> dis(sz, vector<int>(n));
	vector<vector<int>> edge(n, vector<int>());
	
	for(int k=0;k<m;k++) {                     
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}
	
	vector<int> rand(n);
	for(int k=0;k<n;k++) rand[k] = k;
	
	shuffle(rand.begin(), rand.end(), g);
	
	for(int k=0;k<sz;k++) {
		bfs(rand[k], dis[k], edge);
	}
	
	for(int t=0;t<q;t++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		int mn = INT_MAX;
		for(int k=0;k<sz;k++) {
			mn = min(mn, dis[k][a] + dis[k][b]);
		}
		printf("%d", mn);
		printf("%c", t < q - 1? ' ': '\n');
	}
	
}