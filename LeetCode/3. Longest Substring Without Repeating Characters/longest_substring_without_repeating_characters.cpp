/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 *
 * @brief: This problem is solved by keeping track of two pointers. The 'i'
 * pointer is pointing towards a position before the start of the substring
 * whereas the 'j' pointer points to the last element of the substring. The
 * repetition of characters are tracked by an unordered_pair which tracks the
 * characters and their indices. The max length of substring is tracked by
 * max_count. The map updates 'i' pointer to the last seen location of the
 * repeated character by also double checking that the new postion of 'i' is not
 * behind its current position.
 *
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
   public:
    int lengthOfLongestSubstring(std::string s) {
        const int sz = s.size();
        if (sz == 0) {
            return 0;
        } else if (sz == 1) {
            return 1;
        }
        int i = -1;
        int j = 0;
        int max_count = 1;
        std::unordered_map<char, int> map;
        while (i < sz && j < sz) {
            if (map.find(s[j]) != map.end() && map[s[j]] >= i) {
                i = map[s[j]];
            }
            max_count = std::max(max_count, j - i);
            map[s[j]] = j;
            ++j;
        }
        return max_count;
    }
};

int main() {
    const std::vector<std::string> vec_str{"abcabcbb", "bbbbb", "pwwkew",
                                           "abba"};
    Solution sol;
    for (auto str : vec_str) {
        std::cout << sol.lengthOfLongestSubstring(str) << std::endl;
    }
}
