// O(n^2 * m)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define N 105
#define M 5005
using namespace std;
struct DSJ {
    int n;
    vector<int> fa, sz;
    DSJ () {}
    DSJ (int _n) {
        n = _n;
        fa = vector<int> (n+1);
        sz = vector<int> (n+1);
        REP(i,1,n) fa[i] = i;
        REP(i,1,n) sz[i] = 1;
    }
    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }
    void con(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            fa[fy] = fx;
            sz[fx] += sz[fy];
        }
    }
    int size(int x) {
        return sz[find(x)];
    }
};
int n, m, len[M];
char in[N][M];
DSJ dsj;
void init() {
    m = 0;
    REP(i,1,n) {
        scanf("%s", in[i]);
        len[i] = strlen(in[i]);
        m = max(m, len[i]);
    }

    REP(i,1,n) {
        int adj = (m-1) - (len[i]-1);
        for (int j = len[i]-1; j>=0; j--) in[i][j+adj] = in[i][j];
        for (int j = 0; j < m-len[i]; j++) in[i][j] = '0';
        in[i][m] = '\0';
    }
}
bool check(int x, int y) {
    vector<int> diffp;
    REP(i,0,m-1) {
        if (in[x][i] != in[y][i]) {
            diffp.emplace_back(i);
            if (diffp.size() > 2) return false;
        }
    }

    if (diffp.size() == 2) {
        int p1 = diffp[0];
        int p2 = diffp[1];
        if (in[x][p1] == in[y][p2] && in[x][p2] == in[y][p1]) return true;
    }
    return false;
}
int main()
{
    while (~scanf("%d", &n)) {
        init();

        dsj = DSJ(n);
        REP(i,1,n) REP(j,i+1,n) {
            if (check(i, j)) {
                dsj.con(i, j);
            }
        }

        int groups = 0;
        int mx_size = 0;
        REP(i,1,n) {
            if (dsj.find(i) == i) groups++;
            mx_size = max(mx_size, dsj.size(i));
        }
        printf("%d %d\n", groups, mx_size);
    }
    return 0;
}
