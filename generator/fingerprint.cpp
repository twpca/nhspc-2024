#include <bits/stdc++.h>

#include "jngen.h"
using ll = long long;
using namespace std;

void gen(char fn[], int c) {
    FILE *f = fopen(fn, "w");
    ll l = 2, r = 1000;
    if (c == 2) {
        l = 1e4;
        r = 5e4;
    }
    int n = rnd.next(l, r);
    int m = 2 * n - 2;

    vector<int> p(m);
    p[1] = 0;
    p[0] = -1;

    unordered_map<int, int> ust;
    vector<unordered_map<int, int>::iterator> rec;

    ust[0] = 0;
    ust[1] = 0;

    for (auto it = ust.begin(); it != ust.end(); it++) {
        it->second = rec.size();
        rec.emplace_back(it);
    }

    int cur = 2;
    while ((int)rec.size() < n) {
        int x = rnd.next(0, (int)rec.size() - 1);
        swap(rec[x], rec.back());

        int tmp = rec.back()->first;
        ust.erase(rec.back());
        rec.pop_back();

        p[cur] = tmp;
        ust[cur] = rec.size();
        rec.emplace_back(ust.find(cur));

        p[cur + 1] = tmp;
        ust[cur + 1] = rec.size();
        rec.emplace_back(ust.find(cur + 1));

        cur += 2;
    }

    vector<int> tfm(m, -1);
    int cnt = 0;
    for (auto it : rec) {
        tfm[it->first] = ++cnt;
    }
    for (int &i : tfm) {
        if (i == -1) i = ++cnt;
    }
    fprintf(f, "%d\n", m);
    for (int i = 0; i < m; i++) {
        if (p[i] != -1) {
            fprintf(f, "%d %d\n", tfm[p[i]], tfm[i]);
        }
    }
}

void gen2(char fn[], int c, int i) {
    FILE *f = fopen(fn, "w");
    ll l = 500, r = 1000;
    if (c == 3) {
        l = 5e5;
        r = 1e6;
    }
    int n = r;
    int k = rnd.next((2, (int)sqrt(n)));
    if (i > 8) {
        k = rnd.next((int)sqrt(n), n);
    }

    auto T = Tree::kary(n, k);
    int R = rnd.next(0, n - 1);
    auto P = T.parents(R);
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        if (P[i] == -1) continue;
        fprintf(f, "%d %d\n", i + 1, P[i] + 1);
    }

    return;
}

void gen3(char fn[], int c) {
    FILE *f = fopen(fn, "w");
    ll l = 1e5, r = 1e5;
    int n = rnd.next(l, r);

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        if (i != 0) fprintf(f, "%d %d\n", i + 1, 1);
    }

    return;
}

void gen4(char fn[], int c) {
    FILE *f = fopen(fn, "w");
    
    ll n = 1e5;
    if (c == 1)
        n = 1e3;

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n / 4; i++) {
        if (i != 0) fprintf(f, "%d %d\n", i, i + 1);
    }

    for (int i = n / 4; i < n / 2; i++) {
        fprintf(f, "%d 1\n", i + 1);
    }
    
    for (int i = n / 2; i < n; i++) {
        fprintf(f, "%d %d\n", i + 1, n / 4 + 1);
    }

    return;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv);
    int c = atoi(argv[2]);

    char f[40];
    for (int i = 1; i <= 15; i++) {
        sprintf(f, "%d_%02d.in", c, i);
        if (c > 2 && i == 1) {
            gen3(f, c);
            continue;
        }
        if (c != 2 and i == 2) {
            gen4(f, c);
            continue;
        }

        if (c == 2)
            gen(f, c);
        else
            gen2(f, c, i);
    }
}

