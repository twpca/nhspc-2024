#include<bits/stdc++.h>

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

bool change() {
	uniform_int_distribution<> r(0, 1);
	if (r(rng)) return true;
	return false;
}

void output(FILE *fp, int n, vector<pair<int, int>> &edge, vector<pair<int, int>> &query, bool shouldRand) {
	vector<int> rand(n);
	for(int k=0;k<n;k++) rand[k] = k;
	if (shouldRand) {
		shuffle(rand.begin(), rand.end(), rng);
	}
	fprintf(fp, "%d %d %d\n", n, edge.size(), query.size());
	if (n > 5) {
		shuffle(edge.begin(), edge.end(), rng);
	}
	for(auto p: edge) {
		fprintf(fp, "%d %d\n", rand[p.first] + 1, rand[p.second] + 1);
	}
	for(auto p: query) {
		fprintf(fp, "%d %d\n", rand[p.first] + 1, rand[p.second] + 1);
	}
}

void link(int x, int y, vector<pair<int, int>> &edge, map<pair<int, int>, bool> &has) {
	if (change()) swap(x, y);
	edge.push_back(make_pair(x, y));
	if (x > y) swap(x, y);
	has[make_pair(x, y)] = true;
}

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

vector<vector<int>> solve(int n, vector<pair<int, int>> &edge) {
	vector<vector<int>> dis(n, vector<int>(n));
	vector<vector<int>> edges(n, vector<int>());
	
	for(auto p: edge) {                     
		int a = p.first, b = p.second;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	
	for(int k=0;k<n;k++) {
		bfs(k, dis[k], edges);
	}
	
	return dis;
}

void completeQuery(int n, int q, vector<pair<int, int>> &query, vector<vector<int>> &dis) {
	int d = sqrt(n);
	if (d * d <= n) d++;
					
	uniform_int_distribution<> r(0, n - 1);
					
	while (query.size() < q) {
		int a = r(rng), b = r(rng);
		if (dis[a][b] >= d) {
			query.push_back(make_pair(a, b));
		}
	}
}

void add(int x, vector<vector<int>> &over, vector<pair<int, int>> &query) {
	uniform_int_distribution<> rr(0, over[x].size() - 1);
	int y = over[x][rr(rng)];
	if (change()) swap(x, y);
	query.push_back(make_pair(x, y));
}

void completeQueryForTask3(int n, int q, vector<pair<int, int>> &query, vector<vector<int>> &dis, int co) {
	int d = sqrt(n);
	if (d * d <= n) d++;
					
	vector<vector<int>> over(n, vector<int>());
	
	for(int k=0;k<n;k++) {
		for(int i=0;i<n;i++) {
			if (dis[k][i] >= d) {
				over[k].push_back(i);
			}
		}
	}
	
	vector<int> tmp;
	
	for(int k=0;k<n;k++) {
		if (over[k].size() > 0) {
			tmp.push_back(k);
		}
	}
	
	int sz = min((int) tmp.size(), co);
	
	shuffle(tmp.begin(), tmp.end(), rng);
	
	for(int k=0;k<sz;k++) {
		add(tmp[k], over, query);
	}
	
	while (query.size() < q) {
		uniform_int_distribution<> rr(0, sz - 1);
		add(tmp[rr(rng)], over, query);
	}
}

int getRandFromGroup(int x, int E) {
	int a = x * E, b = (x + 1) * E - 1;
	uniform_int_distribution<> r(a, b);
	return r(rng);
}

void gen(char fn[], int subtaskId, int taskId) {
	FILE *fp = fopen(fn, "w");
	vector<pair<int, int>> edge, query;
	map<pair<int, int>, bool> has;
	int n, m, q;
	bool shouldRand = false;
	switch(subtaskId) {
		case 0: {
			n = 4;
			edge.push_back(make_pair(0, 1));
			edge.push_back(make_pair(1, 2));
			edge.push_back(make_pair(2, 3));
			query.push_back(make_pair(0, 3));
			query.push_back(make_pair(3, 0));
			break;
		}
		case 1: {
			switch(taskId) {
				case 1: {
					n = 500, m = 500, q = 30000; shouldRand = true;
					for(int k=0;k<n;k++) {
						int x = k, y = k + 1;
						if (y == n) y = 0;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					break;
				}
				case 2: {
					n = 477, m = 520, q = 7523; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					uniform_int_distribution<> rr(0, n - 1);
					
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					
					break;
				}
				case 3: {
					n = 488, m = 45123, q = 27451; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					vector<bool> dont(n, false);
	
					uniform_int_distribution<> r(70, 100);
					
					int now = 0;
					
					for(int k=0;k<6;k++) {
						now += r(rng);
						for(int i=now;i<=now+35;i++) {
							dont[i] = true;
						}
					}
					
					uniform_int_distribution<> rr(0, n - 1);
	
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (dont[a] || dont[b]) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					
					break;
				}
				case 4: {
					n = 500, m = 12451, q = 26374; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					uniform_int_distribution<> rr(0, 200);
	
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					
					break;
				}	
			}
			break;
		}
		case 2: {
			switch(taskId) {
				case 1: {
					n = 5000, m = 5000, q = 30000; shouldRand = true;
					for(int k=0;k<n;k++) {
						int x = k, y = k + 1;
						if (y == n) y = 0;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					
					break;
				}
				case 2: {
					n = 4777, m = 4899, q = 26451; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					uniform_int_distribution<> rr(0, n - 1);
	
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					
					break;
				}
				case 3: {
					n = 5000, m = 10000, q = 30000; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					vector<bool> dont(n, false);
	
					uniform_int_distribution<> r(100, 160);
					
					int now = 0;
					
					for(int k=0;k<30;k++) {
						now += r(rng);
						for(int i=now;i<=now+90;i++) {
							dont[i] = true;
						}
					}

					uniform_int_distribution<> rr(0, n - 1);
					
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (dont[a] || dont[b]) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					
					break;
				}
				case 4: {
					n = 3871, m = 9999, q = 28631; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					uniform_int_distribution<> rr(0, 689);
	
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					completeQuery(n, q, query, dis);
					
					break;
				}
			}
			break;
		}
		// for case 3 & 4
		default: {
			switch (taskId) {
				case 1: {
					n = 10000, m = 100000, q = 30000;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					uniform_int_distribution<> ra(0, 4947), rb(5059, 9999);
					
					while (edge.size() < 44566) {
						int a = ra(rng), b = ra(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					while (edge.size() < m) {
						int a = rb(rng), b = rb(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					if (subtaskId == 3) {
						completeQueryForTask3(n, q, query, dis, 1000);
					} else {
						completeQuery(n, q, query, dis);
					}
					break;
				}
				case 2: {
					n = 10000, m = 100000, q = 30000; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					uniform_int_distribution<> ra(0, 4947), rb(5059, 9999);
					
					while (edge.size() < 44566) {
						int a = ra(rng), b = ra(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					while (edge.size() < m) {
						int a = rb(rng), b = rb(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					if (subtaskId == 3) {
						completeQueryForTask3(n, q, query, dis, 1000);
					} else {
						completeQuery(n, q, query, dis);
					}
					break;
				}
				case 3: {
					n = 9735, m = 88681, q = 26969; shouldRand = true;
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					uniform_int_distribution<> ra(0, 2123), rb(7560, 9734);
					
					while (edge.size() < 38914) {
						int a = ra(rng), b = ra(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					while (edge.size() < m) {
						int a = rb(rng), b = rb(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					if (subtaskId == 3) {
						completeQueryForTask3(n, q, query, dis, 788);
					} else {
						completeQuery(n, q, query, dis);
					}
					
					break;
				}
				case 4: {
					n = 10000, m = 100000, q = 30000; shouldRand = true;
					const int G = 50, E = 102;
	
					for(int k=0;k<G;k++) {
						for(int i=0;i<E-1;i++) {
							link(k * E + i, k * E + i + 1, edge, has);
						}
					}
					
					int now = G * E;
	
					for(int k=0;k<G-1;k++) {
						// link Group k and k + 1
						link(getRandFromGroup(k, E), now, edge, has);
						for(int i=0;i<100;i++) {
							if (i == 99) {
								link(getRandFromGroup(k + 1, E), now++, edge, has);
							} else {
								link(now, now + 1, edge, has);
								now++;
							}
						}
					}
					
					uniform_int_distribution<> r(0, G - 1);
					
					while (edge.size() < m) {
						int group = r(rng);
						int a = getRandFromGroup(group, E), b = getRandFromGroup(group, E);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					if (subtaskId == 3) {
						completeQueryForTask3(n, q, query, dis, 880);
					} else {
						completeQuery(n, q, query, dis);
					}
					
					break;
				}
				case 5: {
					n = 9888, m = 96351, q = 29631; shouldRand = true; 
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					vector<bool> dont(n, false);
	
					uniform_int_distribution<> r(125, 210);
					
					int now = 0;
					
					for(int k=0;k<42;k++) {
						now += r(rng);
						for(int i=now;i<=now+120;i++) {
							dont[i] = true;
						}
					}
					
					uniform_int_distribution<> rr(0, n - 1);
					
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (dont[a] || dont[b]) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					if (subtaskId == 3) {
						completeQueryForTask3(n, q, query, dis, 993);
					} else {
						completeQuery(n, q, query, dis);
					}
					
					break;
				}
				case 6: {
					n = 10000, m = 100000, q = 30000; shouldRand = true; 
					for(int k=0;k<n-1;k++) {
						int x = k, y = k + 1;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					vector<bool> dont(n, false);
	
					uniform_int_distribution<> r(140, 223);
					
					int now = 0;
					
					for(int k=0;k<45;k++) {
						now += r(rng);
						for(int i=now;i<=now+136;i++) {
							dont[i] = true;
						}
					}
					
					uniform_int_distribution<> rr(0, n - 1);
					
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (dont[a] || dont[b]) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (change()) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					if (subtaskId == 3) {
						completeQueryForTask3(n, q, query, dis, 1000);
					} else {
						completeQuery(n, q, query, dis);
					}
					
					break;
				}
				case 7: {
					n = 10000, m = 100000, q = 30000; shouldRand = true; 
					
					for(int k=0;k<n;k++) {
						int x = k, y = k + 1;
						if (y == n) y = 0;
						if (change()) swap(x, y);
						link(x, y, edge, has);
					}
					
					uniform_int_distribution<> rr(0, 999);
	
					while (edge.size() < m) {
						int a = rr(rng), b = rr(rng);
						if (a == b) continue;
						if (a > b) swap(a, b);
						if (has[make_pair(a, b)]) continue;
						if (rand() & 1) swap(a, b);
						link(a, b, edge, has);
					}
					
					auto dis = solve(n, edge);
					
					if (subtaskId == 3) {
						completeQueryForTask3(n, q, query, dis, 1000);
					} else {
						int d = sqrt(n);
						if (d * d <= n) d++;
						
						for(int k=0;k<n;k++) {
							for(int i=k;i<n;i++) {
								if (dis[k][i] == d) {
									query.push_back(make_pair(k, i));
								}
							}
						}
						
						completeQuery(n, q, query, dis);
					}
					
					break;
				}
			}			
			break;
		}
	}
	output(fp, n, edge, query, shouldRand);
}

const int testcaseNum[5] = {1, 4, 4, 7, 7};

int main(int argc, char *argv[]) {
	int seed = atoi(argv[1]);
    int subtaskId = atoi(argv[2]);
// int main() {
// 	int seed = 1337;
//    int subtaskId = 3;
    char f[40];
    rng = mt19937_64(seed);
    for(int k=1;k<=testcaseNum[subtaskId];k++) {
    	sprintf(f, "%d_%02d.in", subtaskId, k);
    	gen(f, subtaskId, k);
	}
}