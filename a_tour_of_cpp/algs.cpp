#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {
        std::vector<int> vec;
        for (int i = 0; i < 10; ++i) {
                vec.push_back(10-i);
        }
        std::ranges::sort(vec);
        for (auto i: vec)
                std::cout << i << " ";
        return 0;
}
