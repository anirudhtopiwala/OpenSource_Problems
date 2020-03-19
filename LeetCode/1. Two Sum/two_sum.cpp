/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 */
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int,int> map;
        std::vector<int> ans;
        for (int i = 0 ; i< nums.size(); i++){
            int neg = target - nums[i];
            if (map.find(neg)!= map.end()){
                ans.emplace_back(i);
                ans.emplace_back(map.find(neg)->second);
                return ans;
            }
            map[nums[i]] = i;
        }
        
        return ans;
    }
};

int main(){
    std::vector<int> vec{1,2,3,4,3,1,4,2};
    Solution sol;
    auto pair = sol.twoSum(vec,4);
    for(auto val : pair){
        std::cout<< val<< " ";
    }
    std::cout<<std::endl;
}