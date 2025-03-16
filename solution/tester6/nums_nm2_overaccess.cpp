// O(n * m^2), over access map
// Expect: subtask TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define N 105
#define M 5005
using namespace std;
using LL = long long;
constexpr int H = 133;
constexpr LL MOD = 1000000000000007LL;

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
LL pw[M], nh[N];
DSJ dsj;
unordered_map<LL,int> mp;
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
void work() {
    mp.clear();
    pw[0] = 1;
    REP(i,1,m) pw[i] = (pw[i-1] * H) % MOD;
    REP(i,1,n) {
        LL h = 0;
        REP(j,0,m-1) h = (h + pw[j] * in[i][j]) % MOD;
        mp[h] = i;
        nh[i] = h;
    }

    dsj = DSJ(n);
    REP(i,1,n) REP(j,0,m-1) REP(k,j+1,m-1) {
        LL h = (nh[i] - pw[j]*in[i][j] - pw[k]*in[i][k] + pw[k]*in[i][j] + pw[j]*in[i][k]) % MOD;
        h = (h+MOD) % MOD;
        if (mp[h] && mp[h] != i) {
            dsj.con(i, mp[h]);
        }
    }
}
int main()
{
    while (~scanf("%d", &n)) {
        init();
        work();

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
