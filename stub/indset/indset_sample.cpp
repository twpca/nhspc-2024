#include <vector>

bool compare_subsets(const std::vector<int>& a, const std::vector<int>& b);

namespace {
    // 如果需要，你可以在這裡宣告全域變數
    int len;
}

void init(int n) {
    len = n;
}

std::vector<int> range_MWIS_query(int l, int r) {
    return {r};
}
