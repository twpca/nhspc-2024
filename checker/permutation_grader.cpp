#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cassert>

// Functions to be implemented in the solution.
void bob_init(int n);
int query_from_alice(int a);

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
    int n, k, init_done;
    long long p[2002];
    long long query_count, Q;
    void wrong_answer(const std::string &msg) {
        std::cout << "Wrong Answer: " << msg << std::endl;
        exit(0);
    }
    void check_number(int a) {
        if (a < 1 || a > n)
            wrong_answer("Invalid position: " + std::to_string(a));
    }
}

bool compare_numbers(int a, int b) {
    if (init_done)
        wrong_answer("Invalid call");
    // BEGIN SECRET
    query_count = decode(query_count);
    // END SECRET
    query_count += 1;
    // BEGIN SECRET
    query_count = encode(query_count);
    // END SECRET
    check_number(a);
    check_number(b);
    if (a == b)
        wrong_answer("Identical position: " + std::to_string(a));
    // BEGIN SECRET
    p[a] = decode(p[a]);
    p[b] = decode(p[b]);
    // END SECRET
    bool res = p[a] < p[b];
    // BEGIN SECRET
    p[a] = encode(p[a]);
    p[b] = encode(p[b]);
    // END SECRET
    return res;
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> p[i];
    }
    std::vector<long long> query(k);
    for (long long &a : query) {
        std::cin >> a;
        // BEGIN SECRET
        a = decode(a);
        // END SECRET
    }
    // BEGIN SECRET
    query_count = encode(query_count);
    // END SECRET
    bob_init(n);
    // BEGIN SECRET
    long long record_query_count = query_count;
    query_count = decode(query_count);
    // END SECRET
    Q = (query_count + n - 1) / n;
    // BEGIN SECRET
    Q = encode(Q);
    query_count = encode(query_count);
    // END SECRET

    std::vector<long long> ans(k);
    for (int i = 0; i < k; ++i) {
        ans[i] = query_from_alice(static_cast<int>(query[i]));
    }

    // BEGIN SECRET
    if (record_query_count != query_count)
        wrong_answer("Malicious behavior");
    // END SECRET
    for (int i = 0; i < k; ++i)
        std::cout << ans[i] << " \n"[i + 1 == k];
    std::cout << "Accepted: " << Q << std::endl;

    return 0;
}
