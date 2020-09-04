/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-10
 * Last Edit Date: 2020-10
 *
 * @brief The question can be found here
 *  949. Largest Time for Given Digits
 * (https://leetcode.com/problems/largest-time-for-given-digits/)
 */

#include <algorithm>
#include <string>
#include <vector>

class Solution {
   public:
    std::string largestTimeFromDigits(std::vector<int> &A) {
        std::string max_time = "";
        std::sort(A.begin(), A.end());
        int max_minutes = -1;
        int curr_time;
        do {
            if (!is_valid_time(A, &curr_time)) {
                continue;
            }
            if (curr_time > max_minutes) {
                max_minutes = curr_time;
                max_time = std::to_string(A[0]) + std::to_string(A[1]) + ":" +
                           std::to_string(A[2]) + std::to_string(A[3]);
            }
        } while (std::next_permutation(A.begin(), A.end()));
        return max_time;
    }

    bool is_valid_time(const std::vector<int> &time, int *curr_time) {
        const int &hours = time[0] * 10 + time[1];
        const int &minutes = time[2] * 10 + time[3];
        *curr_time = hours * 60 + minutes;
        return (hours < 24 && minutes < 60) ? true : false;
    }
};
