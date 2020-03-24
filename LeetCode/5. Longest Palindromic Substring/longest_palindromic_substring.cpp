/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 *
 * @brief: This solution is an O(N^2) solution. The idea is that for each character 
 * in the string start expanding and checking for odd and even palindromes. This works
 * because if a longer sibstring is a palindrome then the small substring inside it 
 * has to be a palindrome. We check for odd and even because we are not sure about
 * the length of the substring. 
 * 
 */
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string longestPalindrome(std::string s) {
      std::string res = "";
      if (s.size() == 0){
        return res;
      }
      if (s.size() == 1){
        return s;
      }
      int max_len = 1;
      int start = 0;
      for (int i =1; i < s.size(); ++i){
        // For odd Palindromes 
          int left = i-1;
          int right = i+1;
          while (left >= 0 && right < s.size() && s[left] == s[right]){
            if (right - left + 1 > max_len){
              max_len = right - left + 1;
              start = left;
            }
            --left;
            ++right;
          }
        // For Even Palindromes 
          left = i-1;
          right = i;
          while (left >= 0 && right < s.size() && s[left] == s[right]){
            if (right - left + 1 > max_len){
              max_len = right - left + 1;
              start = left;
            }
            --left;
            ++right;
          }
      }
    return s.substr(start,max_len);
    }
};

int main() {
  const std::vector<std::string> vec_str {"babad", "cbbd", "pwwkew","abba", "abcd"}; 
  Solution sol;
  for (auto str : vec_str) {
    std::cout<<sol.longestPalindrome(str)<<std::endl;
  }
}