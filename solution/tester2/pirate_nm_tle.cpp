#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 10005, Q = 30005, M = 200005;
int d[N], que[N], head[N], to[M], nxt[M], tot;
int head2[N], to2[Q], nxt2[Q], qid[Q], ans[Q], tot2;

void add(int u, int v) {
    tot++;
    to[tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void add2(int u, int v, int id) {
    tot2++;
    to2[tot2] = v;
    qid[tot2] = id;
    nxt2[tot2] = head2[u];
    head2[u] = tot2;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= q; ++i) {
        int u, v;
        std::cin >> u >> v;
        add2(u, v, i);
    }

    for (int s = 1; s <= n; ++s) {
        memset(d, -1, sizeof(d));
        d[s] = 0;
        que[0] = s;
        for (int i = 0, sz = 1; i < sz && sz < n; ++i) {
            int v = que[i];
            for (int j = head[v]; j; j = nxt[j]) {
                int u = to[j];
                if (d[u] == -1) {
                    d[u] = d[v] + 1;
                    que[sz++] = u;
                }
            }
        }
        for (int i = head2[s]; i; i = nxt2[i]) {
            int v = to2[i], id = qid[i];
            ans[id] = d[v];
        }
    }

    for (int i = 1; i <= q; ++i)
        std::cout << ans[i] << " \n"[i == q];
}