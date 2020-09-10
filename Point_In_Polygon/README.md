# Is the Point inside the Polygon?

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---
## Overview
"In computational geometry, the point-in-polygon (PIP) problem asks whether a given point in the plane lies inside, outside, or on the boundary of a polygon." - Wikipedia. Some methods to solve the PIP problem is by using [Ray Casting algorithm](https://en.wikipedia.org/wiki/Point_in_polygon) and [Winding Number algorithm](https://en.wikipedia.org/wiki/Point_in_polygon). In this project I have explained the winding number algorithm and discussed a method to solve PIP for convex polygons. A detailed explanation of the theory behind the code can be found on my medium post [here](https://medium.com/@topiwala.anirudh/is-the-point-inside-the-polygon-574b86472119?source=friends_link&sk=4ad22e08ea43bab588c94e6aa94266e6).

## Dependencies
To run this program you need to have the following installed on your system:
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page): To work with vectors.

## Build Instructions

To build this code, run the following commands:
```
cd ~
git clone https://github.com/anirudhtopiwala/OpenSource_Problems.git
cd ~/OpenSource_Problems/Point_In_Polygon/
mkdir build
cd build
cmake ..
make
```

## Running the node
To run the node
```
./is_inside_polygon
```

This will test some query points for differently shaped polygons. Feel free to play wih the query points and  different polygon shapes.
