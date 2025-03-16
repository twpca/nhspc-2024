#include <iostream>
#include <utility>
#include <vector>
#include <numeric>
#include <random>

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, k;
    std::cin >> n >> k;
    std::vector<std::pair<int, int>> points(n);
    for (auto &[x, y] : points)
        std::cin >> x >> y;
    
    auto cross = [&](std::pair<int, int> p, std::pair<int, int> q) {
        return (long long)p.first * q.second - (long long)q.first * p.second; 
    };

    auto collinear = [&](std::pair<int, int> p, std::pair<int, int> q, std::pair<int, int> r) {
        return cross(std::make_pair(q.first - p.first, q.second - p.second), std::make_pair(r.first - p.first, r.second - p.second)) == 0; 
    };

    auto check = [&](std::pair<int, int> p, std::pair<int, int> q) {
        int cnt = 0;
        for (auto r : points)
            cnt += collinear(p, q, r);
        return cnt >= k;
    };

    std::mt19937 rng(20241207);

    auto yes = [&]() {
        std::cout << "Yes\n";
        exit(0);
    };
    
    if (n > 300) {
        int T = 60;
        while (T--) {
            int u = 0, v = 0;
            while (u == v) {
                u = rng() % n;
                v = rng() % n;
            }
            if (check(points[u], points[v]))
                yes();
        }
    }
    else {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (check(points[i], points[j]))
                    yes();
    }

    std::cout << "No\n";
}
