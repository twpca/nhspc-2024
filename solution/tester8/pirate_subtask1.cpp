#include<bits/stdc++.h>

using namespace std;

const int INF = 1000000;

void FloydWarshall(vector<vector<int>> &dis) {
	int n = dis.size();
	for(int k=0;k<n;k++) {
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				if (dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}	
}

int main() {
	
//	freopen("input_4-1.txt", "r", stdin);
//	freopen("output_4-1_test1.txt", "w", stdout);
	
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	vector<vector<int>> dis(n, vector<int>(n, 0));
	
	for(int k=0;k<n;k++) {
		for(int i=0;i<n;i++) {
			if (k == i) dis[k][i] = 0;
			else dis[k][i] = INF;
		}
	}
	
	for(int k=0;k<m;k++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		dis[a][b] = dis[b][a] = 1;
	}
	
	FloydWarshall(dis);
	
	for(int t=0;t<q;t++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		printf("%d", dis[a][b]);
		printf("%c", t < q - 1? ' ': '\n');
	}
}