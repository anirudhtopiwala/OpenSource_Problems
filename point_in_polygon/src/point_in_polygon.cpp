/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-08
 * Last Edit Date: 2020-08
 *
 * @brief Implements two funtions:
 *         1) Check if a point is inside a polygon using windinding number
 *            algorithm.
 *         2) A simpler way to check if a point is inside a convex polygon.
 *
 */

#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

/**
 * @brief The result can be used to test if the query point lies on the left or
 *        right side of the line formed by pt1 and pt2 when viewed in
 *        anticlockwise  direction.
 *
 * @param pt1: First point to form equation of line.
 * @param pt2: Second point to form equation of line.
 * @param query_point: Query point
 * @return: > 0: Query point lies on left of the line.
 *          = 0: Query point lies on the line.
 *          < 0: Query point lies on right of the line.
 */
double substitute_point_in_line(const Eigen::Vector2d &pt1,
                                const Eigen::Vector2d &pt2,
                                const Eigen::Vector2d &query_point) {
    return ((query_point.y() - pt1.y()) * (pt2.x() - pt1.x())) -
           ((query_point.x() - pt1.x()) * (pt2.y() - pt1.y()));
};

/**
 * @brief Check if a point lies inside, on or outside a convex polygon.
 *
 * For a convex polygon, if the sides of the polygon can be considered as a path
 * from first vertex. Then, a query point is said to be inside the polygon if it
 * lies on the same side of all the line segments making up the path.
 *
 * @param query_point Point to check.
 * @param vertices Vertices making up the polygon.
 * @return  = 1: query_point lies inside the polygon.
 *          = 0: query_point lies on the polygon.
 *          =-1: query_point lies outside the polygon.
 */
int is_point_inside_convex_polygon(const Eigen::Vector2d &query_point,
                                   std::vector<Eigen::Vector2d> &vertices) {
    const int num_sides_of_polygon = vertices.size();
    int count_same_side_results = 0;
    // Iterate over each side.
    for (size_t i = 0; i < num_sides_of_polygon; ++i) {
        const auto point_in_line = substitute_point_in_line(
            vertices[i], vertices[(i + 1) % num_sides_of_polygon], query_point);

        // Check if the point lies on the polygon.
        if (point_in_line == 0) {
            return point_in_line;
        }

        count_same_side_results += point_in_line > 0;
    }
    return (std::abs(count_same_side_results) == num_sides_of_polygon) ? 1 : -1;
}

/**
 * @brief Check if a point lies inside, on or outside any polygon.
 *
 * Winding number algorithm can be used to check if any point lies inside a
 * polygon. A more detailed explanation can be found in the blog post here.
 *
 *
 * @param query_point Point to check.
 * @param vertices Vertices making up the polygon in anticlockwise direction.
 * @return  = 1: query_point lies inside the polygon.
 *          = 0: query_point lies on the polygon.
 *          =-1: query_point lies outside the polygon.
 */
int is_point_inside_polygon(const Eigen::Vector2d &query_point,
                            std::vector<Eigen::Vector2d> &vertices) {
    int wn = 0;  // the  winding number counter
    const int num_sides_of_polygon = vertices.size();

    for (size_t i = 0; i < num_sides_of_polygon; ++i) {
        const auto point_in_line = substitute_point_in_line(
            vertices[i], vertices[(i + 1) % num_sides_of_polygon], query_point);

        // Check if the point lies on the polygon.
        if (point_in_line == 0) {
            return 0;
        }
        if (vertices[i].y() <= query_point.y()) {
            // Upward crossing.
            if (vertices[(i + 1) % num_sides_of_polygon].y() >
                query_point.y()) {
                if (point_in_line > 0) {
                    ++wn;  // query point is left of edge
                }
            }
        } else {
            // Downward crossing.
            if (vertices[(i + 1) % num_sides_of_polygon].y() <
                query_point.y()) {
                if (point_in_line < 0) {
                    --wn;  // query point is right of edge
                }
            }
        }
    }
    return (wn != 0) ? 1 : -1;  // Point is inside polygon only if wn != 0
}

int main() {
    // Map to make printing easier.
    std::unordered_map<int, std::string> get_value{
        {-1, "outisde"}, {0, "on"}, {1, "inside"}};
    // Non Convex Polygon
    {
        std::cout << "For Non Convex Polygon...\n" << std::endl;
        // Vetices need to be in anticlockwise direction to fix the notion of
        // left and right of edges made in the comments.
        std::vector<Eigen::Vector2d> vertices{{0, 0}, {3, 1}, {6, 0}, {3, 5}};
        std::vector<Eigen::Vector2d> query_points{
            {3, 2}, {3, 6}, {3, 1}, {0, 0}, {15, 20}};
        for (const auto &point : query_points) {
            std::cout << "Point: " << point.transpose() << " lies "
                      << get_value[is_point_inside_polygon(point, vertices)]
                      << " the polygon." << std::endl;
        }
    }

    // Convex Polygons
    std::cout << "For Convex Polygon..." << std::endl;
    // Triangle
    {
        std::cout << "For Triangle\n" << std::endl;
        std::vector<Eigen::Vector2d> vertices{{0, 0}, {6, 0}, {3, 5}};
        std::vector<Eigen::Vector2d> query_points{
            {3, 2}, {3, 6}, {3, 5}, {0, 0}, {15, 20}};
        for (const auto &point : query_points) {
            std::cout << "Point: " << point.transpose() << " lies "
                      << get_value[is_point_inside_polygon(point, vertices)]
                      << " the polygon." << std::endl;
        }
    }

    // Quadrilateral
    {
        std::cout << "For convex Quadrilateral\n" << std::endl;
        std::vector<Eigen::Vector2d> vertices{{0, 0}, {6, 0}, {6, 6}, {-1, 10}};
        std::vector<Eigen::Vector2d> query_points{
            {3, 2}, {3, 6}, {3, 5}, {0, 0}, {15, 20}};
        for (const auto &point : query_points) {
            std::cout << "Point: " << point.transpose() << " lies "
                      << get_value[is_point_inside_polygon(point, vertices)]
                      << " the polygon." << std::endl;
        }
    }
}
