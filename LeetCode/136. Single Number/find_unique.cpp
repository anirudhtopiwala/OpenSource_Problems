/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 */

#include <iostream>
#include <vector>

template <typename T>
class Solution {
   public:
    T singleNumber(std::vector<T>& nums) {
        T num = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            num = num ^ nums[i];
        }
        return num;
    }
};

int main() {
    Solution<int> sol;
    std::vector<int> vec{1, 2, 2, 2, 2, 1, 3};
    std::cout << sol.singleNumber(vec) << std::endl;
}
