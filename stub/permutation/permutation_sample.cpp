#include <vector>
#include <numeric>
#include <algorithm>

bool compare_numbers(int a, int b);

namespace {
    // 如果需要，你可以在這裡宣告全域變數
    std::vector<int> perm;
}

void bob_init(int n) {
    perm.resize(n);
    std::iota(perm.begin(), perm.end(), 1);
    if (!compare_numbers(perm[0], perm[1])) {
        std::swap(perm[0], perm[1]);
    }
}

int query_from_alice(int a) {
    return perm[a - 1];
}
