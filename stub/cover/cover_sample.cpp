#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int testcase = 1;
    std::string input_file = "input_" + std::to_string(testcase) + "_1.txt";
    std::string output_file = "output_" + std::to_string(testcase) + "_1.txt";
    freopen(input_file.c_str(), "r", stdin);
    freopen(output_file.c_str(), "w", stdout);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> grid(5 * n, std::vector<int>(5 * m));
    for (auto &v : grid)
        for (int &i : v)
            std::cin >> i;
    for (auto &v : grid) {
        bool first = true;       
        for (int &i : v) {
            if (!first) std::cout << " ";
            else first = false;
            std::cout << i;
        }
        std::cout << "\n";
    }    
    std::cerr << "Finished!\n";
}
