#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <numeric>
#include <utility>
#include <cmath>
#include <algorithm>
#include <set>
#include <cassert>
#include "testlib.h"

#define register_generator(name) if (gname == #name) return name(argc - 2, argv + 2), 0

const int C = 1000000000;

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

std::pair<int, int> gen_random_point(int xl, int xr, int yl, int yr) {
    int x = rnd.next(xl, xr);
    int y = rnd.next(yl, yr);
    return std::make_pair(x, y);
}

std::vector<std::pair<int, int>> get_line(int n, int x0, int y0) {
    std::vector<std::pair<int, int>> vec;
    int mix = C, miy = C, lx = -C, ly = -C;
    
    while (true) {
        std::pair<int, int> dp = gen_random_point(-C / n, C / n, -C / n, C / n);
        
        auto dist = distinct(n, 0, C / std::max(std::abs(dp.first), std::abs(dp.second)));
        std::sort(dist.begin(), dist.end());

        if (x0) dp.first = 0;
        if (y0) dp.second = 0;

        mix = C, miy = C, lx = -C, ly = -C;
        vec.clear();
        for (int f : dist) {
            std::pair<int, int> p = std::make_pair(dp.first * f, dp.second * f);
            mix = std::min(mix, C - p.first);
            miy = std::min(miy, C - p.second);
            lx = std::max(lx, -C - p.first);
            ly = std::max(ly, -C - p.second);
            vec.push_back(p);
        }
        if (lx <= mix && ly <= miy) break;
    }

    std::pair<int, int> sp = gen_random_point(lx, mix, ly, miy);

    for (auto &[x, y] : vec) {
        x += sp.first;
        y += sp.second;
    }

    shuffle(vec.begin(), vec.end());

    return vec;
}

void gen(int argc, char *argv[]) { // n k
    int n = atoi(argv[0]);
    int k = atoi(argv[1]);
    int d = atoi(argv[2]);
    int x0 = atoi(argv[3]);
    int y0 = atoi(argv[4]);
    
    auto vec = get_line(k - d, x0, y0);
    
    std::set<std::pair<int, int>> vis(vec.begin(), vec.end());
    
    while (int(vis.size()) < n) {
        std::pair<int, int> p = gen_random_point(-C, C, -C, C);
        if (vis.insert(p).second)
            vec.push_back(p);
    }

    shuffle(vec.begin(), vec.end());
    
    printf("%d %d\n", n, k);
    for (auto &[x, y] : vec)
        printf("%d %d\n", x, y);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return std::cerr << "Arguments should not be empty.\n", 1;
    }
    registerGen(argc, argv, 1);
    std::string gname(argv[1]);
    register_generator(gen);
    return 0;
}
