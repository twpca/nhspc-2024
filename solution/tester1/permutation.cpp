#include <vector>
#include <algorithm>

bool compare_numbers(int a, int b);

namespace global {
    std::vector<int> perm;
    bool compare_numbers(int a, int b) {
        return ::compare_numbers(a + 1, b + 1);
    }
}

void bob_init(int n) {
    global::perm.resize(n);
    std::vector<int> pos;
    for (int i = 0; i < n; ++i) {
        pos.insert(std::lower_bound(pos.begin(), pos.end(), i, [&](int a, int b) {
            return global::compare_numbers(a, b);
        }), i); 
    }
    for (int i = 0; i < n; ++i)
        global::perm[pos[i]] = i;
}

int query_from_alice(int a) {
    return global::perm[a - 1] + 1;
}
