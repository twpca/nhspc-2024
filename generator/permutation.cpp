#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>
#include "testlib.h"

#define register_generator(name) if (gname == #name) return name(argc - 2, argv + 2), 0

long long encode(long long x) {
    // omitted in public repo
    return x;
}
long long decode(long long x) {
    // omitted in public repo
    return x;
}

/* Returns random permutation of the given size (values are between `first` and `first` + size - 1)*/
template<typename T, typename E>
std::vector<E> perm(T size, E first) {
    assert (size > 0);
    std::vector<E> p(size);
    E current = first;
    for (T i = 0; i < size; i++)
        p[i] = current++;
    if (size > 1)
        for (T i = 1; i < size; i++)
            std::swap(p[i], p[rnd.next(i + 1)]);
    return p;
}

/* Returns `size` unordered (unsorted) distinct numbers between `from` and `to`. */
template<typename T>
std::vector<T> distinct(int size, T from, T to) {
    std::vector<T> result;
    if (size == 0)
        return result;

    assert (from <= to);

    assert (size >= 0);

    uint64_t n = to - from + 1;
    assert (uint64_t(size) <= n);

    double expected = 0.0;
    for (int i = 1; i <= size; i++)
        expected += double(n) / double(n - i + 1);

    if (expected < double(n)) {
        std::set<T> vals;
        while (int(vals.size()) < size)
            vals.insert(T(rnd.next(from, to)));
        result.insert(result.end(), vals.begin(), vals.end());
    } else {
        assert (n <= 1000000000);
        std::vector<T> p(perm(int(n), from));
        result.insert(result.end(), p.begin(), p.begin() + size);
    }

    return result;
}

void gen(int argc, char *argv[]) { // n sorted
    int n = atoi(argv[0]);
    int sorted = atoi(argv[1]);
    
    std::vector<long long> arr(n);
    std::iota(arr.begin(), arr.end(), 1);
    if (sorted == -1)
        std::reverse(arr.begin(), arr.end());
    else if (sorted == 0)
        shuffle(arr.begin(), arr.end());
    std::vector<long long> query(n);
    std::iota(query.begin(), query.end(), 1);
    shuffle(query.begin(), query.end());

    printf("%d %d\n", n, n);
    for (int i = 0; i < n; ++i)
        printf("%lld%c", encode(arr[i]), " \n"[i + 1 == n]);
    for (int i = 0; i < n; ++i)
        printf("%lld%c", encode(query[i]), " \n"[i + 1 == n]);
}

void gen_sample(int argc, char *argv[]) {
    int n = 3, k = 2;
    std::vector<long long> arr({3, 1, 2});
    std::vector<long long> query({1, 2});

    printf("%d %d\n", n, k);
    for (int i = 0; i < n; ++i)
        printf("%lld%c", encode(arr[i]), " \n"[i + 1 == n]);
    for (int i = 0; i < k; ++i)
        printf("%lld%c", encode(query[i]), " \n"[i + 1 == k]);
}

void gen_hack_sort(int argc, char *argv[]) {
    int n = atoi(argv[0]);
    int rev = atoi(argv[1]);
    auto dfs1 = [&](auto dfs, int l, int r) -> std::vector<int> {
        if (r - l + 1 <= 5) {
            std::vector<int> ret(r - l + 1);
            std::iota(ret.begin(), ret.end(), l);
            return ret;
        }
        int mid = (l + r + 1) / 2;
        std::vector<int> ret(r - l + 1, -1);
        ret[r - l] = r;
        ret[mid - l] = r - 1;
        std::vector<int> tmp = dfs(dfs, l, r - 2);
        int ptr = 0;
        for (int i = 0; i < r - l + 1; ++i)
            if (ret[i] == -1) ret[i] = tmp[ptr++];
        return ret;
    };
    std::vector<int> a = dfs1(dfs1, 1, n);
    if (rev) std::reverse(a.begin(), a.end());

    std::vector<long long> query(n);
    std::iota(query.begin(), query.end(), 1);
    shuffle(query.begin(), query.end());

    printf("%d %d\n", n, n);
    for (int i = 0; i < n; ++i)
        printf("%lld%c", encode(a[i]), " \n"[i + 1 == n]);
    for (int i = 0; i < n; ++i)
        printf("%lld%c", encode(query[i]), " \n"[i + 1 == n]);

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return std::cerr << "Arguments should not be empty.\n", 1;
    }
    registerGen(argc, argv, 1);
    std::string gname(argv[1]);
    register_generator(gen);
    register_generator(gen_sample);
    register_generator(gen_hack_sort);
    return 0;
}
