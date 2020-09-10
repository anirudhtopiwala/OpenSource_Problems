cmake_minimum_required(VERSION 3.2.1)
project (point_in_polygon)

add_compile_options(-std=c++17)

find_package (Eigen3 REQUIRED NO_MODULE)

include_directories(include ${EIGEN3_INCLUDE_DIR} )

add_executable(is_inside_polygon src/point_in_polygon.cpp)

target_link_libraries(is_inside_polygon)
