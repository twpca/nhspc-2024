#include<random>
#include<tuple>
#include<vector>
#include<cstdio>
using namespace std;

constexpr int MN_T = 0;
constexpr int MX_T[] = {-1, 0, 1, 2, 1'000'000, 1'000'000};
constexpr int MN_N = 1;
constexpr int MX_N = 10'000'000;

struct Gen{
    Gen() = default;
    constexpr void next() noexcept{
        ++subtask, file = 0;
    }
    void gen(tuple<int, vector<int>> const &input){
        char fn[32];
        sprintf(fn, "%d_%02d.in", subtask, ++file);
        FILE *fout = fopen(fn, "wb");
        auto [t, n] = input;
        fprintf(fout, "%d\n", t);
        for (int i = 0; i <= t; ++i)
            fprintf(fout, "%d%c", n[i], " \n"[i == t]);
        fclose(fout);
    }
    int subtask = 0, file = 0;
};

std::mt19937_64 Rng(71);
using Unif = std::uniform_int_distribution<>;
int rand_intvl(int l, int r){
    return Unif(l, r)(Rng);
}

vector<int> randomize(int t, int l, int r) {
    vector<int> n(t + 1);
    for (int &i : n)
        i = rand_intvl(l, r);
    return n;
}


int main() {
    Gen g;
    g.next();

    {
        g.gen({0, {MN_N}});
        g.gen({0, {54316}});
        g.gen({0, {MX_N}});
        g.next();
    }

    {
        g.gen({1, {4360, 1}});
        g.gen({1, {23, MX_N}});
        g.gen({1, {MX_N, 269123}});
        g.gen({1, {MX_N, MX_N}});
        g.next();
    }

    {
        for (int i = 1; i <= 2; ++i)
            g.gen({2, randomize(2, MN_N, MX_N)});
        g.gen({2, {1, MX_N, 63491}});
        g.gen({2, {MX_N, MX_N, MX_N}});
        g.next();
    }

    {
        for (int i = 1; i <= 2; ++i) {
            int t = rand_intvl(MN_T, MX_T[5] - 1);
            vector<int> n = randomize(t, MN_N, MX_N);
            g.gen({t, n});
        }
        vector<int> n = randomize(MX_T[5], MN_N, MX_N);
        g.gen({MX_T[5], n});
        n = randomize(MX_T[5], 5'000'000, MX_N);
        n[0] = MX_N;
        n[6347] = MX_N;
        g.gen({MX_T[5], n});
    }
}
