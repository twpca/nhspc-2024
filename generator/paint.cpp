#include <bits/stdc++.h>

using Unif = std::uniform_int_distribution<>;
constexpr int MN_K[] = {-1, 1, 2, 4};
constexpr int MX_K[] = {-1, 2, 3, 7};
constexpr int MN_N[] = {-1, 1, 1, 900000};
constexpr int MX_N[] = {-1, 1000000, 1000, 1000000};
std::mt19937_64 rng;

void gen_case(char fn[], int c) {
    FILE *f = fopen(fn, "w");
    int K = Unif(MN_K[c], MX_K[c])(rng);
    int N = Unif(MN_N[c], MX_N[c])(rng);

    std::vector<char> carr(52);
    for(int i = 0; i < 26; i++){
        carr[i] = 'a' + i;
        carr[i+26] = 'A' + i;
    }
    std::shuffle(carr.begin(), carr.end(), rng);

    while(N--){
        fprintf(f, "%c", carr[Unif(0, K-1)(rng)]);
    }
    fprintf(f, "\n");
    fclose(f);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("./test2 seed test_No");
        assert(0);
    }

    int s = atoi(argv[1]);
    int c = atoi(argv[2]);
    rng = std::mt19937_64(s);

    char f[40];
    for (int i=1; i<=20; i++) {
        sprintf(f, "%d_%02d.in", c, i);
        gen_case(f, c);
    }
}