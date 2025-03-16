#include "testlib.h"
#include <bits/stdc++.h>

using ll = long long;

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

/* Returns `size` unordered (unsorted) distinct numbers between `from` and `to`. */
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

/* Returns `size` unordered (unsorted) distinct numbers between `0` and `upper`-1. */
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

/* Returns random (unsorted) partition which is a representation of sum as a sum of integers not less than min_part. */
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

long long iceil(long long a, long long b){
	return a / b + (a % b && (a < 0) ^ (b > 0));
}

bool hasOpt(const std::string &key) {
    return __testlib_opts.find(key) != __testlib_opts.end();
}

// ===

template<typename T>
std::vector<T> partition(int size, T sum, T min_part, T max_part) {
    auto tmp = partition(size, sum, min_part);
    T too_much = 0;
    for (int i = 0; i < size; i++) {
        if (tmp[i] > max_part) {
            too_much += tmp[i] - max_part;
            tmp[i] = max_part;
        }
    }
    for (int i = 0; i < size; i++) {
        if (tmp[i] < max_part) {
            T cur = std::min(max_part - tmp[i], too_much);
            too_much -= cur;
            tmp[i] += cur;
        }
    }
    T tsum = 0;
    for (int i = 0; i < size; i++) {
        assert(min_part <= tmp[i] && tmp[i] <= max_part);
        tsum += tmp[i];
    }
    assert(tsum == sum);
    return tmp;
}


const int SUB34_MAX_K = 1000;
const int SUB5_MAX_K = 100000;
const int MAX_K = 1'000'000'000;
const int MAX_A[6] = {0, 100, 100, 1000, 100000, 1000000000};

struct Testcase {
    int n, K;
    std::vector<int> a;
    Testcase(int _n = 0, int _K = 0): n(_n), K(_K), a(n + 1) {}
};

bool check_yes(int n, int K, long long sum_a) {
    int g = std::gcd(n, K);
    return K % n != 0 && sum_a % g == 0;
}

Testcase gen_random(int n, int K, bool yes) {
    int subtask = opt<int>("subtask");
    if (yes && K % n == 0) K = 1;
    if (!yes && std::gcd(n, K) == 1) K = n;
    int max_a = hasOpt("max_a") ? opt<int>("max_a") : MAX_A[subtask];
    Testcase testcase(n, K);
    auto &a = testcase.a;
    long long total_a = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = rnd.next(0, max_a);
        total_a += a[i];
    }
    if (yes != check_yes(n, K, total_a)) {
        int g = std::gcd(n, K);
        int need = yes ? g - total_a % g : (total_a % g == 0 ? 1 : 0);
        while (need) {
            int x = rnd.next(1, n);
            if (a[x] == MAX_A[subtask]) continue;
            a[x]++;
            total_a++;
            need--;
        }
    }
    std::sort(a.begin() + 1, a.end());
    if (a[1] == a[n]) {
        if (a[1] > 1) a[1]--, total_a--;
        else a[n]++, total_a++;
    }
    assert(yes == check_yes(n, K, total_a));
    return testcase;
}

Testcase gen_random2(int n, int K, bool yes) {
    int subtask = opt<int>("subtask");
    if (yes && K % n == 0) K = 1;
    if (!yes && std::gcd(n, K) == 1) K = n;
    int g = std::gcd(n, K);
    long long min_min_a = hasOpt("min_min_a") ? opt<long long>("min_min_a") : 0LL;
    long long max_min_a = hasOpt("max_min_a") ? opt<long long>("max_min_a") : (long long) MAX_A[subtask];
    long long min_max_a = hasOpt("min_max_a") ? opt<long long>("min_max_a") : 0LL;
    long long max_max_a = hasOpt("max_max_a") ? opt<long long>("max_max_a") : (long long) MAX_A[subtask];
    long long min_sum_a = hasOpt("min_sum_a") ? opt<long long>("min_sum_a") : 0LL;
    long long max_sum_a = hasOpt("max_sum_a") ? opt<long long>("max_sum_a") : (long long) MAX_A[subtask] * n;
    long long min_a = rnd.next(min_min_a, max_min_a);
    long long max_a = rnd.next(min_max_a, max_max_a);
    long long sum_a = rnd.next(min_sum_a, max_sum_a);
    if (yes) {
        sum_a = sum_a / g * g;
        if (sum_a == 0) sum_a += g;
    }
    max_a = std::max(max_a, (sum_a + n - 1) / n);
    max_a = std::min(max_a, sum_a);
    min_a = std::min(min_a, (sum_a - max_a) / (n - 1));
    if (sum_a - max_a * (n - 1) > 0)
        min_a = std::max(min_a, sum_a - max_a * (n - 1));

    Testcase testcase(n, K);
    auto &a = testcase.a;
    auto tmp = partition(n - 2, sum_a - min_a - max_a, min_a, max_a);
    a[1] = min_a; a[n] = max_a;
    for (int i = 2; i < n; i++) a[i] = tmp[i - 2];

    std::sort(a.begin() + 1, a.end());
    if (a[1] == a[n]) {
        a[1]--, a[n]++;
    }
    assert(yes == check_yes(n, K, sum_a));
    return testcase;
}

Testcase gen_fix(int n, int K, int min_a, int max_a, bool yes) {
    int g = std::gcd(n, K);
    if (yes && K % n == 0) K = 1;
    long long sum_a_min = (long long) min_a * (n - 1) + max_a;
    long long sum_a_max = (long long) max_a * n;
    long long sum_a = yes ? rnd.next(iceil(sum_a_min, g), sum_a_max / g) * g : rnd.next(sum_a_min, sum_a_max);
    if (!yes && sum_a % g == 0) {
        if (sum_a + 1 <= sum_a_max) sum_a++;
        else sum_a--;
    }

    Testcase testcase(n, K);
    auto &a = testcase.a;
    a[1] = min_a;
    a[n] = max_a;
    auto tmp = partition(n - 2, sum_a - min_a - max_a, (long long) min_a, (long long) max_a);
    for (int i = 2; i < n; i++)
        a[i] = tmp[i - 2];
    std::sort(a.begin() + 1, a.end() - 1);
    assert(std::accumulate(a.begin(), a.end(), 0LL) == sum_a);
    return testcase;
}

Testcase gen_construct(int n, int K, int t, int add) {
    int subtask = opt<int>("subtask");
    if (K % n == 0) K = 1;
    //std::cerr << n << " " << K << " " << t * (K % n) << " " << t << "\n";
    int min_k = 0;
    int max_k = std::min(t, min_k + MAX_A[subtask]);
    while ((long long) max_k * n <= (long long) t * (K % n)) {
        min_k++;
        max_k = std::min(t, min_k + MAX_A[subtask]);
    }

    auto k = partition(n, (long long) t * (K % n), (long long) min_k, (long long) max_k);
    std::sort(k.begin(), k.end(), std::greater<>());
    //std::cerr << "QQ " << k[0] << " " << k[n - 1] << "\n";
    int p = rnd.next(k[0], MAX_A[subtask] + k[n - 1]);
    Testcase testcase(n, K);
    auto &a = testcase.a;
    for (int i = 1; i <= n; i++) {
        a[i] = p - k[i - 1];
    }
    while (add--) {
        int i = rnd.next(1, n);
        if (a[i] < MAX_A[subtask]) a[i]++;
    }
    sort(a.begin() + 1, a.end());
    if (a[1] == a[n]) a[n]++;
    return testcase;
}

Testcase generator_random(int n) {
    int subtask = opt<int>("subtask");
    double yes_probability = opt<double>("yes_probability");
    bool yes = rnd.next() < yes_probability;
    if (subtask == 1) return gen_random(n, 1, yes);
    if (subtask == 2) return gen_random(n, n - 1, yes);
    if (subtask == 3) return gen_random(n, rnd.next(1, SUB34_MAX_K), yes);
    if (subtask == 4) return gen_random(n, rnd.next(1, SUB5_MAX_K), yes);
    if (subtask == 5) return gen_random(n, rnd.next(1, MAX_K), yes);
    assert(false);
}

Testcase generator_random2(int n) {
    int subtask = opt<int>("subtask");
    double yes_probability = opt<double>("yes_probability");
    bool yes = rnd.next() < yes_probability;
    if (subtask == 1) return gen_random2(n, 1, yes);
    if (subtask == 2) return gen_random2(n, n - 1, yes);
    if (subtask == 3) return gen_random2(n, rnd.next(1, SUB34_MAX_K), yes);
    if (subtask == 4) return gen_random2(n, rnd.next(1, SUB5_MAX_K), yes);
    if (subtask == 5) return gen_random2(n, rnd.next(1, MAX_K), yes);
    assert(false);
}

Testcase generator_Kzero(int n) {
    int subtask = opt<int>("subtask");
    if (subtask == 1) assert(false);
    if (subtask == 2) assert(false);
    if (subtask == 3) return gen_random(n, rnd.next(1, SUB34_MAX_K / n) * n, false);
    if (subtask == 4) return gen_random(n, rnd.next(1, SUB5_MAX_K / n) * n, false);
    if (subtask == 5) return gen_random(n, rnd.next(1, MAX_K / n) * n, false);
    assert(false);
}

Testcase generator_fix(int n) {
    int subtask = opt<int>("subtask");
    int diff_min = opt<int>("diff_min");
    int diff_max = opt<int>("diff_max");
    int diff = rnd.next(diff_min, diff_max);
    int min_a = rnd.next(1, MAX_A[subtask] - diff);
    int max_a = min_a + diff;
    double yes_probability = opt<double>("yes_probability");
    bool yes = rnd.next() < yes_probability;
    if (subtask == 1) return gen_fix(n, 1, min_a, max_a, yes);
    if (subtask == 2) return gen_fix(n, n - 1, min_a, max_a, yes);
    if (subtask == 3) return gen_fix(n, rnd.next(1, SUB34_MAX_K), min_a, max_a, yes);
    if (subtask == 4) return gen_fix(n, rnd.next(1, SUB5_MAX_K), min_a, max_a, yes);
    if (subtask == 5) return gen_fix(n, rnd.next(1, MAX_K), min_a, max_a, yes);
    assert(false);
}

Testcase generator_construct(int n) {
    int subtask = opt<int>("subtask");
    int min_t = opt<int>("min_t");
    int max_t = opt<int>("max_t");
    int min_add = opt<int>("min_add");
    int max_add = opt<int>("max_add");
    int t = rnd.next(min_t, max_t);
    int add = rnd.next(min_add, max_add);
    int force_k = hasOpt("force_k") ? opt<int>("force_k") : -1;
    if (subtask == 1) return gen_construct(n, 1, t, add);
    if (subtask == 2) return gen_construct(n, n - 1, t, add);
    if (subtask == 3) return gen_construct(n, force_k != -1 ? force_k : rnd.next(1, SUB34_MAX_K), t, add);
    if (subtask == 4) return gen_construct(n, force_k != -1 ? force_k : rnd.next(1, SUB5_MAX_K), t, add);
    if (subtask == 5) return gen_construct(n, force_k != -1 ? force_k : rnd.next(1, MAX_K), t, add);
    assert(false);
}

Testcase generator_only_one(int n) {
    int an = opt<int>("an");
    int K = opt<int>("k");
    Testcase testcase(n, K);
    testcase.a[n] = an;
    return testcase;
}

void enumerate_all() {
    int n = opt<int>("n");
    int max_sum_a = opt<int>("max_sum_a");
    std::vector<Testcase> testcases;
    int max_sum_n = opt<int>("sum_n");
    int sum_n = 0;
    for (int sum_a = 1; sum_a <= max_sum_a; sum_a++) {
        if (sum_n + n > max_sum_n) break;
        for (int min_a = 0; min_a <= sum_a / n; min_a++) {
            if (sum_n + n > max_sum_n) break;
            for (int max_a = std::max(min_a + 1, (sum_a - min_a + n - 1 - 1) / (n - 1)); max_a <= sum_a - min_a * (n - 1); max_a++) {
                if (sum_n + n > max_sum_n) break;
                for (int K = 1; K < n; K++) {
                    Testcase testcase(n, K);
                    if (sum_n + n > max_sum_n) break;
                    auto tmp = partition(n - 2, sum_a - min_a - max_a, min_a, max_a);
                    for (int i = 2; i <= n - 1; i++) testcase.a[i] = tmp[i - 2];
                    testcase.a[1] = min_a;
                    testcase.a[n] = max_a;
                    testcases.emplace_back(testcase);
                    sum_n += n;
                }
            }
        }
    }
    std::cout << testcases.size() << "\n";
    for (auto &testcase : testcases) {
        std::cout << testcase.n << " " << testcase.K << "\n";
        sort(testcase.a.begin(), testcase.a.end());
        for (int i = 1; i <= n; i++)
            std::cout << testcase.a[i] << " \n"[i == n];
    }
}

int main(int argc, char *argv[]){
    registerGen(argc, argv, 1);

    std::string generator_str = argv[1];

    if (generator_str == "enumerate") {
        enumerate_all();
        return 0;
    }

    int T = opt<int>("T");
    int sum_n = opt<int>("sum_n");
    int subtask = opt<int>("subtask");

    std::vector<std::string> generators(1);
    for (char c : generator_str)
        if (c == ',') generators.emplace_back();
        else generators.back() += c;

    std::map<std::string, std::function<Testcase(int)>> generator_func;
    generator_func["random"] = generator_random;
    generator_func["Kzero"] = generator_Kzero;
    generator_func["fix"] = generator_fix;
    generator_func["construct"] = generator_construct;
    generator_func["only_one"] = generator_only_one;
    generator_func["random2"] = generator_random2;

    std::vector<int> ns = partition<int>(T, sum_n, 2);
    std::vector<int> ans_distribute;
    if (subtask == 4 && generator_str == "construct" && T > 1) {
        double yes_probability = hasOpt("yes_probability") ? opt<double>("yes_probability") : 1.0;
        int num_yes = yes_probability * T;
        int min_t = opt<int>("min_t");
        int max_t = opt<int>("max_t");
        int sum_t = rnd.next(min_t, max_t);
        if (num_yes) ans_distribute = partition<int>(num_yes, sum_t);
        ans_distribute.resize(T, -1);
    }
    shuffle(ans_distribute.begin(), ans_distribute.end());

    std::cout << T << "\n";
    int index = -1;
    for (int i : ns) {
        index++;
        std::string generator_name = rnd.any(generators);

        assert(generator_func.find(generator_name) != generator_func.end());
        Testcase testcase;
        if (subtask == 4 && generator_name == "construct" && T > 1) {
            int force_k = hasOpt("force_k") ? opt<int>("force_k") : -1;
            if (ans_distribute[index] == -1) testcase = gen_random(i,  force_k != -1 ? force_k : rnd.next(1, SUB5_MAX_K), false);
            else testcase = gen_construct(i, force_k != -1 ? force_k : rnd.next(1, SUB5_MAX_K), ans_distribute[index], 0);
        }
        else 
            testcase = generator_func[generator_name](i);

        if (hasOpt("force_a1")) {
            int diff = opt<int>("force_a1") - testcase.a[1];
            for (int i = 1; i <= testcase.n; i++)
                testcase.a[i] += diff;
        }

        std::cout << testcase.n << " " << testcase.K << "\n";
        for (int i = 1; i <= testcase.n; i++)
            std::cout << testcase.a[i] << " \n"[i == testcase.n];

    }

}
