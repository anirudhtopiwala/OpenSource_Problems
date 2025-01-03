/*
 * MIT License
 * Copyright (c) 2025 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2025-01
 * Last Edit Date: 2025-01
 *
 * @brief Implementation of geometric median for a 2D grid with >= 0 targets.
 *
 */
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <vector>

// Function to find the point minimizing the distance to target points
std::pair<int, int>
geometric_median(const std::vector<std::vector<std::string>> &grid) {
  if (grid.empty() || grid[0].empty()) {
    return {-1, -1};
  }

  std::vector<std::vector<int>> distances(grid.size(),
                                          std::vector<int>(grid[0].size(), 0));
  std::vector<std::vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  for (int row = 0; row < grid.size(); ++row) {
    for (int col = 0; col < grid[0].size(); ++col) {
      if (grid[row][col] == "*") {
        std::queue<std::pair<int, int>> to_explore;
        std::vector<std::vector<bool>> visited(
            grid.size(), std::vector<bool>(grid[0].size(), false));
        std::vector<std::vector<int>> distance_per_target(
            grid.size(), std::vector<int>(grid[0].size(), 0));

        to_explore.push({row, col});
        visited[row][col] = true;

        while (!to_explore.empty()) {
          const auto curr_node = to_explore.front();
          to_explore.pop();

          for (const auto &direction : directions) {
            const int new_row = curr_node.first + direction[0];
            const int new_col = curr_node.second + direction[1];

            if (new_row >= 0 && new_row < grid.size() && new_col >= 0 &&
                new_col < grid[0].size() && grid[new_row][new_col] != "#" &&
                !visited[new_row][new_col]) {
              to_explore.push({new_row, new_col});
              visited[new_row][new_col] = true;
              distance_per_target[new_row][new_col] =
                  distance_per_target[curr_node.first][curr_node.second] + 1;
            }
          }
        }

        for (int i = 0; i < grid.size(); ++i) {
          for (int j = 0; j < grid[0].size(); ++j) {
            distances[i][j] += distance_per_target[i][j];
          }
        }
      }
    }
  }

  int min_row, min_col = -1;
  int min_distance = std::numeric_limits<int>::max();
  for (int row = 0; row < distances.size(); ++row) {
    for (int col = 0; col < distances[0].size(); ++col) {
      if (grid[row][col] != "#" && distances[row][col] < min_distance) {
        min_distance = distances[row][col];
        min_row = row;
        min_col = col;
      }
    }
  }
  return {min_row, min_col};
}

int main() {
  // Test Case 1: Simple 3x3 grid
  std::vector<std::vector<std::string>> grid1 = {
      {" ", " ", " "},
      {" ", "*", " "},
      {" ", " ", " "}}; // Median point: (1, 1)

  // Test Case 2: 5x5 grid with multiple targets
  std::vector<std::vector<std::string>> grid2 = {
      {" ", " ", "*", " ", " "},
      {" ", " ", " ", " ", " "},
      {"*", " ", " ", " ", "*"},
      {" ", " ", " ", " ", " "},
      {" ", " ", "*", " ", " "}}; // Median point: (2, 2)

  // Test Case 3: 5x5 grid with walls and uneven targets
  std::vector<std::vector<std::string>> grid3 = {
      {"#", "#", "*", "#", "#"},
      {" ", "#", " ", " ", " "},
      {"*", "#", " ", " ", "*"},
      {" ", " ", " ", "#", " "},
      {"#", "#", "*", "#", "#"}}; // Median point: (2, 2)

  // Test Case 4: Large 7x7 grid with clustered targets
  std::vector<std::vector<std::string>> grid4 = {
      {" ", " ", " ", " ", " ", " ", " "}, {" ", "*", "*", " ", " ", " ", " "},
      {" ", "*", "*", " ", " ", " ", " "}, {" ", " ", " ", " ", " ", " ", " "},
      {" ", " ", " ", "*", "*", "*", " "}, {" ", " ", " ", "*", "*", "*", " "},
      {" ", " ", " ", " ", " ", " ", " "}}; // Median point: (4, 3)

  // Test Case 5: Edge-heavy targets on 6x6 grid
  std::vector<std::vector<std::string>> grid5 = {
      {"*", " ", " ", " ", " ", "*"},
      {" ", " ", " ", " ", " ", " "},
      {" ", " ", "*", " ", "*", " "},
      {" ", " ", " ", " ", " ", " "},
      {" ", " ", " ", " ", " ", " "},
      {"*", " ", " ", " ", " ", "*"}}; // Median point: (2, 2)

  // Run tests
  std::vector<std::vector<std::vector<std::string>>> test_cases = {
      grid1, grid2, grid3, grid4, grid5};
  std::vector<std::pair<int, int>> expected_results = {
      {1, 1}, {2, 2}, {2, 2}, {4, 3}, {2, 2}};

  for (size_t i = 0; i < test_cases.size(); ++i) {
    std::pair<int, int> result = geometric_median(test_cases[i]);
    std::cout << "Test Case " << i + 1 << ": ";
    if (result == expected_results[i]) {
      std::cout << "Passed\n";
    } else {
      std::cout << "Failed (Expected: (" << expected_results[i].first << ", "
                << expected_results[i].second << ") Got: (" << result.first
                << ", " << result.second << "))\n";
    }
  }

  return 0;
}
