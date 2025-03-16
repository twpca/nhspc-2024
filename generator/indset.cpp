#include "testlib.h"
#include <iostream>
#include <cassert>

const int MAXN = 2000;
const int MAXQ = 2000;
const int MAXC = 1'000'000'000;
long long encode(long long x) {
    // omitted in public repo
    return x;
}
long long decode(long long x) {
    // omitted in public repo
    return x;
}

/* Returns random permutation of the given size (values are between `first` and `first`+size-1)*/
template<typename T, typename E>
std::vector<E> perm(T size, E first) {
    if (size < 0)
        __testlib_fail("random_t::perm(T size, E first = 0): size must non-negative");
    else if (size == 0)
        return std::vector<E>();
    std::vector<E> p(size);
    E current = first;
    for (T i = 0; i < size; i++)
        p[i] = current++;
    if (size > 1)
        for (T i = 1; i < size; i++)
            std::swap(p[i], p[rnd.next(i + 1)]);
    return p;
}

/* Returns random permutation of the given size (values are between 0 and size-1)*/
template<typename T>
std::vector<T> perm(T size) {
    return perm(size, T(0));
}

template<typename T>
std::vector<T> distinct(int size, T from, T to) {
    std::vector<T> result;
    if (size == 0)
        return result;

    if (from > to)
        __testlib_fail("random_t::distinct expected from <= to");

    if (size < 0)
        __testlib_fail("random_t::distinct expected size >= 0");

    uint64_t n = to - from + 1;
    if (uint64_t(size) > n)
        __testlib_fail("random_t::distinct expected size <= to - from + 1");

    double expected = 0.0;
    for (int i = 1; i <= size; i++)
        expected += double(n) / double(n - i + 1);

    if (expected < double(n)) {
        std::set<T> vals;
        while (int(vals.size()) < size) {
            T x = T(rnd.next(from, to));
            if (vals.insert(x).second)
                result.push_back(x);
        }
    } else {
        if (n > 1000000000)
            __testlib_fail("random_t::distinct here expected to - from + 1 <= 1000000000");
        std::vector<T> p(perm(int(n), from));
        result.insert(result.end(), p.begin(), p.begin() + size);
    }

    return result;
}

template<typename T>
std::vector<T> distinct(int size, T upper) {
    if (size < 0)
        __testlib_fail("random_t::distinct expected size >= 0");
    if (size == 0)
        return std::vector<T>();

    if (upper <= 0)
        __testlib_fail("random_t::distinct expected upper > 0");
    if (size > upper)
        __testlib_fail("random_t::distinct expected size <= upper");

    return distinct(size, T(0), upper - 1);
}

template<typename T>
std::vector<T> partition(int size, T sum, T min_part) {
    if (size < 0)
        __testlib_fail("random_t::partition: size < 0");
    if (size == 0 && sum != 0)
        __testlib_fail("random_t::partition: size == 0 && sum != 0");
    if (min_part * size > sum)
        __testlib_fail("random_t::partition: min_part * size > sum");
    if (size == 0 && sum == 0)
        return std::vector<T>();

    T sum_ = sum;
    sum -= min_part * size;

    std::vector<T> septums(size);
    std::vector<T> d = distinct(size - 1, T(1), T(sum + size - 1));
    for (int i = 0; i + 1 < size; i++)
        septums[i + 1] = d[i];
    sort(septums.begin(), septums.end());

    std::vector<T> result(size);
    for (int i = 0; i + 1 < size; i++)
        result[i] = septums[i + 1] - septums[i] - 1;
    result[size - 1] = sum + size - 1 - septums.back();

    for (std::size_t i = 0; i < result.size(); i++)
        result[i] += min_part;

    T result_sum = 0;
    for (std::size_t i = 0; i < result.size(); i++)
        result_sum += result[i];
    if (result_sum != sum_)
        __testlib_fail("random_t::partition: partition sum is expected to be the given sum");

    if (*std::min_element(result.begin(), result.end()) < min_part)
        __testlib_fail("random_t::partition: partition min is expected to be no less than the given min_part");

    if (int(result.size()) != size || result.size() != (size_t) size)
        __testlib_fail("random_t::partition: partition size is expected to be equal to the given size");

    return result;
}

/* Returns random (unsorted) partition which is a representation of sum as a sum of positive integers. */
template<typename T>
std::vector<T> partition(int size, T sum) {
    return partition(size, sum, T(1));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>("n");
    int q = opt<int>("q");
    std::string array_type = opt<std::string>("array");
    std::string query_type = opt<std::string>("query");

    std::vector <long long> w(n + 1), ql(q + 1), qr(q + 1);
    std::vector <std::pair<int, int>> cartesian_good;
    if (array_type == "random") {
    	int C = opt<int>("C");
        for (int i = 1; i <= n; ++i)
            w[i] = rnd.next(1, C);
    } else if (array_type == "cartesian") {
        int full = opt<int>("full");
        int start = 1;
        auto push_new_segment = [&](std::vector <int> p) {
            int len = (int)p.size();
            for (int l = start + 2; l <= start + 2 * len; l += 2)
                for (int r = l + 1; r <= start + 2 * len + 1; ++r)
                    cartesian_good.emplace_back(l, r);
            w[start] = 1;
            start += 1;
            w[start] = n * n;
            start += 1;
            int lst = 0;
            for (int i : p) {
                w[start] = n + i - lst;
                start += 1;
                w[start] = n;
                start += 1;
                lst = i;
            }
            w[start] = 1;
            start += 1;
        };
        if (full) {
            for (int l = 1; ; ++l) {
                std::vector <int> p(l);
                for (int i = 0; i < l; ++i)
                    p[i] = i + 1;
                do {
                    if (start + 2 * l + 3 > n)
                        break;
                    push_new_segment(p);
                } while (std::next_permutation(p.begin(), p.end()));
                if (start + 2 * l + 3 > n)
                    break;
            }
            while (start <= n) {
                w[start] = 1;
                start += 1;
            }
        } else {
	        int segment = opt<int>("segment");
	        std::string mode = opt<std::string>("mode");
            std::vector <int> len = partition(segment, (n - segment * 3) / 2, 0);
            for (int l : len) {
                std::vector <int> p(l);
                for (int i = 0; i < l; ++i)
                    p[i] = i + 1;
                if (mode == "random") {
                    shuffle(p.begin(), p.end());
                } else if (mode == "inc") {
	        		int inv = opt<int>("inv");
                    if (l >= 2) {
                        for (int i = 0; i < inv; ++i) {
                            int id = rnd.next(0, l - 2);
                            if (p[id] < p[id + 1])
                                std::swap(p[id], p[id + 1]);
                        }
                    }
                } else if (mode == "dec") {
	        		int inv = opt<int>("inv");
                    if (l >= 2) {
                        for (int i = 0; i < inv; ++i) {
                            int id = rnd.next(0, l - 2);
                            if (p[id] < p[id + 1])
                                std::swap(p[id], p[id + 1]);
                        }
                    }
                    std::reverse(p.begin(), p.end());
                }
                push_new_segment(p);
            }
            if (start == n) {
                w[start] = 1;
                start += 1;
            }
        }
    } else {
        assert(false);
    }

    if (query_type == "random") {
        for (int i = 1; i <= q; ++i) {
            int id = rnd.next(0, n * (n + 1) / 2 - 1);
            for (int l = 1; l <= n; ++l) {
                if (id >= n - l + 1) {
                    id -= n - l + 1;
                } else {
                    ql[i] = l;
                    qr[i] = l + id;
                    break;
                }
            }
        }
    } else if (query_type == "full") {
        assert(q == n * (n + 1) / 2);
        for (int l = 1, id = 1; l <= n; ++l)
            for (int r = l; r <= n; ++r) {
                ql[id] = l;
                qr[id] = r;
                id++;
            }
    } else if (query_type == "l1") {
        assert(q == n);
        for (int i = 1; i <= n; ++i) {
            ql[i] = 1;
            qr[i] = i;
        }
    } else if (query_type == "hardcase") {
        std::vector <int> lst1, lst2, best;
        std::vector <std::pair <int, int>> good;
        for (int i = 1; i <= n; ++i) {
            lst2.push_back(i);
            long long cur = 0;
            for (int id : lst1)
                cur += w[id];
            for (int id : lst2)
                cur -= w[id];
            if (cur < 0)
                best = lst2;
            else
                best = lst1;
            for (int j : best)
                if (j > 1)
                    good.emplace_back(std::make_pair(j - 1, i));
            lst2 = lst1, lst1 = best;
        }
        shuffle(good.begin(), good.end());
        for (int i = 1; i <= q; ++i) {
            ql[i] = good[(i - 1) % (int)good.size()].first;
            qr[i] = good[(i - 1) % (int)good.size()].second;
        }
    } else if (query_type == "cartesian") {
        int spec = opt<int>("cartspec");
        std::vector <std::pair <int, int>> good = cartesian_good;
        if (spec == 0) {
            shuffle(good.begin(), good.end());
            for (int i = 1; i <= q; ++i) {
                ql[i] = good[(i - 1) % (int)good.size()].first;
                qr[i] = good[(i - 1) % (int)good.size()].second;
            }
        } else if (spec == 1) {
            for (int i = 1; i <= q; ++i) {
                ql[i] = good[(i - 1) % (int)good.size()].first;
                qr[i] = good[(i - 1) % (int)good.size()].second;
            }
        } else if (spec == 2) {
            for (int i = 1; i <= q; ++i) {
                ql[i] = good[(i + 1999) % (int)good.size()].first;
                qr[i] = good[(i + 1999) % (int)good.size()].second;
            }
        } else {
            assert(false);
        }
    } else if (query_type == "subtask2") {
        std::vector <long long> dp(n + 1), cnt(n + 1);
        dp[1] = w[1];
        cnt[0] = cnt[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1];
            cnt[i] = cnt[i - 1];
            if (dp[i] < dp[i - 2] + w[i]) {
                dp[i] = dp[i - 2] + w[i];
                cnt[i] = cnt[i - 2];
            } else if (dp[i] == dp[i - 2] + w[i])
                cnt[i] = std::min<long long>(cnt[i] + cnt[i - 2], 2);
        }
        std::vector <int> lst1, lst2, best;
        std::vector <std::pair <int, int>> good;
        for (int i = 1; i <= n; ++i) {
            lst2.push_back(i);
            long long cur = 0;
            for (int id : lst1)
                cur += w[id];
            for (int id : lst2)
                cur -= w[id];
            if (cur < 0)
                best = lst2;
            else
                best = lst1;
            if (cnt[i] == 1) {
                std::vector <bool> valid(n + 1, false);
                for (int j : best) {
                    valid[j] = true;
                    if (j > 2)
                        valid[j - 2] = true;
                }
                for (int j = 1; j <= i; ++j)
                    if (valid[j])
                        good.emplace_back(j, i);
            }
            lst2 = lst1, lst1 = best;
        }
        shuffle(good.begin(), good.end());
        for (int i = 1; i <= q; ++i) {
            ql[i] = good[(i - 1) % (int)good.size()].first;
            qr[i] = good[(i - 1) % (int)good.size()].second;
        }
    } else if (query_type == "special") {
        for (int i = 1, len = n - 3; i <= q; len -= 3) {
            for (int j = 3; j + len <= n && i <= q; j += 3) {
                ql[i] = j;
                qr[i] = j + len;
                i++;
            }
        }
    } else if (query_type == "special2") {
        for (int i = 1; i <= q; ++i) {
            ql[i] = 3;
            qr[i] = n;
        }
    } else {
        assert(false);
    }

    std::cout << encode(n) << " " << encode(q) << "\n";
    for (int i = 1; i <= n; ++i)
        std::cout << encode(w[i]) << " \n"[i == n];
    std::vector <int> ord(q + 1);
    for (int i = 1; i <= q; ++i)
        ord[i] = i;
    shuffle(1 + ord.begin(), ord.end());
    for (int i = 1; i <= q; ++i)
        std::cout << encode(ql[ord[i]]) << " " << encode(qr[ord[i]]) << "\n";
}
