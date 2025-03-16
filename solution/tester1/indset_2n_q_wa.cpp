#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

bool compare_subsets(const std::vector<int>& a, const std::vector<int>& b);

namespace global {
    std::vector<std::vector<int>> opt, rev_opt;
    std::vector<int> prv_cont, nxt_cont;
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
    opt.resize(n, std::vector<int>(n)), rev_opt.resize(n, std::vector<int>(n));
    prv_cont.resize(n, -1), nxt_cont.resize(n, n);

    opt[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        if (i > 1) opt[i] = opt[i - 2];
        opt[i][i] = 1;
        if (!compare_subsets(opt[i - 1], opt[i]))
            opt[i] = opt[i - 1]; 
    }
    for (int r = 0; r < n; ++r)
        for (int i = r; i - 1 >= 0; --i)
            if (!opt[r][i] && !opt[r][i - 1]) {
                prv_cont[r] = i;
                break;
            }
    
    rev_opt[n - 1][n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        if (i + 2 < n)
            rev_opt[i] = rev_opt[i + 2];
        rev_opt[i][i] = 1;
        if (!compare_subsets(rev_opt[i + 1], rev_opt[i]))
            rev_opt[i] = rev_opt[i + 1];
    }
    for (int l = 0; l < n; ++l)
        for (int i = l; i + 1 < n; ++i)
            if (!rev_opt[l][i] && !rev_opt[l][i + 1]) {
                nxt_cont[l] = i;
                break;
            }
}

std::vector<int> range_MWIS_query(int l, int r) {
    if (l == r) return {l};
    using namespace global;
    --l, --r;
    if (l == 0 || !opt[r][l - 1])
        return to_subset(opt[r], l, r);
    if (r == int(opt.size()) - 1 || !rev_opt[l][r + 1])
        return to_subset(rev_opt[l], l, r);
    if (prv_cont[r] - 1 >= l) {
        auto res = range_MWIS_query(l + 1, prv_cont[r]);
        insert_back(res, to_subset(opt[r], prv_cont[r], r));
        return res;
    }
    if (nxt_cont[l] + 1 <= r) {
        auto res = range_MWIS_query(nxt_cont[l] + 2, r + 1);
        auto prv = to_subset(rev_opt[l], l, nxt_cont[l]);
        insert_back(prv, res);
        return prv;
    }
    std::vector<int> res(opt.size()), flip(opt.size());
    set_alt(res, l + 1, r - 1), set_alt(flip, l, r);
    if (compare_subsets(flip, res)) return to_subset(res);
    return to_subset(flip);
}
