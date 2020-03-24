/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 *
 * @brief: This is an extension of two sum. One way to solve this is to add
 * another 'for' loop to the two sum problem. Although in this approach, it is
 * difficult to remove duplicates. To solve this, we can sort the input vector,
 * and for each element then we can have two pointers starting from the left
 * and right of the remaining vector and look for the negative number. This way
 * no duplicates would be added to the result vector.
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    if (nums.size() < 3) {
      return res;
    }
    int neg = 0;
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++) {
      if (i == 0 || (i > 0 && nums[i] != nums[i - 1])) {
        neg = -nums[i];
        int low = i + 1;
        int high = n - 1;
        while (low < high) {
          if (nums[low] + nums[high] == neg) {
            std::vector<int> v = {nums[i], nums[low], nums[high]};
            while (low < high && nums[low] == nums[low + 1]) {
              low++;
            }
            while (low < high && nums[high] == nums[high - 1]) {
              high--;
            }
            low++, high--;
            res.emplace_back(v);
          } else if (nums[low] + nums[high] > neg) {
            high--;
          } else {
            low++;
          }
        }
      }
    }
    return res;
  }
};

int main() {
  std::vector<int> vec{1, 2, -3, 4, 3, -1, 4, 2};
  Solution sol;
  auto res = sol.threeSum(vec);
  for (auto pair : res) {
    for(auto val : pair){
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
}