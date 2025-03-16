#include <vector>
#include <cassert>
#include <algorithm>

bool compare_subsets(const std::vector<int>& a, const std::vector<int>& b);

namespace global {
    std::vector<std::vector<int>> opt, monotone;
    std::vector<int> to_subset(const std::vector<int> &a, int l = 0, int r = opt.size() - 1) {
        std::vector<int> res;
        for (int i = l; i <= r; ++i)
            if (a[i])
                res.push_back(i + 1);
        return res;
    }
    void insert_back(std::vector<int> &a, const std::vector<int> &b) {
        a.insert(a.end(), b.begin(), b.end());
    }
    bool compare_subsets(const std::vector<int> &a, std::vector<int> &b) {
        return ::compare_subsets(to_subset(a), to_subset(b));
    }
    void set_alt(std::vector<int> &a, int l, int r) {
        for (int i = l; i <= r; i += 2)
            a[i] = 1;
    }
}

void init(int n) {
    using namespace global;
    opt.resize(n, std::vector<int>(n)), monotone.resize(n);

    opt[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        if (i > 1) opt[i] = opt[i - 2];
        opt[i][i] = 1;
        if (!compare_subsets(opt[i - 1], opt[i]))
            opt[i] = opt[i - 1]; 
    }

    auto leq = [&](int i, int j) {
        assert((i + j) % 2 == 0);
        assert(i < j);
        std::vector<int> subset[2];
        subset[0].resize(n), subset[1].resize(n);
        for (int k = i + 1; k <= j; ++k)
            subset[(i + k) % 2][k] = 1;
        return compare_subsets(subset[0], subset[1]);
    };
    
    for (int t = 0; t < 2; ++t) {
        std::vector<int> stk;
        for (int i = 1 + t; i < n; i += 2) {
            while (!stk.empty() && leq(stk.back(), i)) 
                stk.pop_back();
            stk.push_back(i);
            monotone[i] = stk;
        }
    }
}

std::vector<int> range_MWIS_query(int l, int r) {
    if (l == r) return {l};
    using namespace global;
    --l, --r;
    if (l == 0 || !opt[r][l - 1])
        return to_subset(opt[r], l, r);
    for (int i = r; i - 1 >= l; --i)
        if (!opt[r][i] && !opt[r][i - 1]) {
            auto res = range_MWIS_query(l + 1, i);
            insert_back(res, to_subset(opt[r], i, r));
            return res;
        }
    int ql = l - 1, qr = r - !opt[r][r];
    int mx = *lower_bound(monotone[qr].begin(), monotone[qr].end(), ql);
    std::vector<int> res(opt.size());
    set_alt(res, l, mx - 1), set_alt(res, mx + 2, qr);
    if (opt[r][r]) return to_subset(res);
    std::vector<int> flip(opt.size());
    set_alt(flip, l, r);
    if (compare_subsets(flip, res)) return to_subset(res);
    return to_subset(flip);
}
