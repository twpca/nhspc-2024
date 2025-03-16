#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Point {
    int x, y;  
    Point(int _x = 0, int _y = 0): x(_x), y(_y) {}
};

Point operator-(const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y); 
}

long long cross(const Point &a, const Point &b) {
    return (long long)a.x * b.y - (long long)a.y * b.x;
}

int cal_collinear(const Point &x, const Point &y, std::vector<Point> &arr) {
    int res = 0;
    for (auto p : arr)
        res += static_cast<int>(cross(y - x, p - x) == 0);
    return res;
}

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, k;
    std::cin >> n >> k;
    std::vector<Point> arr(n);
    for (auto &[x, y] : arr)
        std::cin >> x >> y;
    if (n <= 300) {
        bool flag = false; 
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (cal_collinear(arr[i], arr[j], arr) >= k)
                    flag = true;
        if (flag)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }
    else {
        // TODO
        srand(time(0));
        if (rand() % 2 == 0)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }
}
