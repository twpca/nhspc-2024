#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cassert>

// Functions to be implemented in the solution.
void init(int n);
std::vector <int> range_MWIS_query(int l, int r);

namespace {
    // BEGIN SECRET
    long long encode(long long x) {
        // omitted in public repo
        return x;
    }
    long long decode(long long x) {
        // omitted in public repo
        return x;
    }
    // END SECRET
    long long n, q;
    long long w[2002];
    long long query_left[2002], query_right[2002];
    long long query_count, Q_init, Q_query;
    bool vis[2002];
    std::vector<int> sol[2002];
    void wrong_answer(const std::string &msg) {
        std::cout << "Wrong Answer: " << msg << std::endl;
        exit(0);
    }
    void check_valid_set(const std::vector<int> &a) {
        for (int id : a) {
            if (!(1 <= id && id <= n))
                wrong_answer("Invalid vertex number: " + std::to_string(id));
            if (vis[id])
                wrong_answer("Duplicated vertex number: " + std::to_string(id));
            vis[id] = true;
        }
        for (int id : a)
            vis[id] = false;
    }
    long long get_subset_sum(const std::vector <int> a) {
        long long res = 0;
        for (int id : a)
            res += w[id];
        return res;
    }
}

bool compare_subsets(const std::vector<int>& a, const std::vector<int>& b) {
    // BEGIN SECRET
    query_count = decode(query_count);
    // END SECRET
    query_count += 1;
    // BEGIN SECRET
    query_count = encode(query_count);
    // END SECRET
    check_valid_set(a);
    check_valid_set(b);
    return get_subset_sum(a) < get_subset_sum(b);
}

int main() {
    std::cin >> n >> q;
    // BEGIN SECRET
    n = decode(n);
    q = decode(q);
    // END SECRET
    for (int i = 1; i <= n; ++i) {
        std::cin >> w[i];
        // BEGIN SECRET
        w[i] = decode(w[i]);
        // END SECRET
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> query_left[i] >> query_right[i];
        // BEGIN SECRET
        query_left[i] = decode(query_left[i]);
        query_right[i] = decode(query_right[i]);
        // END SECRET
    }
    // BEGIN SECRET
    query_count = encode(query_count);
    // END SECRET
    init(n);
    // BEGIN SECRET
    query_count = decode(query_count);
    // END SECRET
    Q_init = (query_count + n - 1) / n;
    query_count = 0;
    // BEGIN SECRET
    Q_init = encode(Q_init);
    Q_query = encode(Q_query);
    query_count = encode(query_count);
    // END SECRET


    for (int i = 1; i <= q; ++i) {
        sol[i] = range_MWIS_query(query_left[i], query_right[i]);
        // BEGIN SECRET
        Q_query = decode(Q_query);
        query_count = decode(query_count);
        // END SECRET
        Q_query = std::max(Q_query, query_count);
        query_count = 0;
        // BEGIN SECRET
        Q_query = encode(Q_query);
        query_count = encode(query_count);
        // END SECRET
    }

    for (int i = 1; i <= q; ++i) {
        std::cout << (int)sol[i].size() << std::endl;
        for (int j = 0; j < (int)sol[i].size(); ++j) {
            if (j > 0)
                std::cout << " ";
            std::cout << sol[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "Accepted: " << Q_init << " " << Q_query << std::endl;

    return 0;
}
