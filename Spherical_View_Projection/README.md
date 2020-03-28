# Spherical View Projection

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---
## Overview
Spherical Projection or Front View projection is nothing but a way to represent the 3D point cloud data into 2D image data, and so essentially it also acts as a dimensionality reduction method. Spherical projection is increasingly being used in a variety of deep learning applications like object classification and segmentation. The theory and derivation of the Spherical projection can be found on my medium post [here](https://medium.com/@topiwala.anirudh/spherical-projection-for-point-clouds-56a2fc258e6c).

## Demonstration of the Project

Here the the upper part shows the intensity values for the spherical image formed from the point cloud shown in the lower part. The data below is taken from sequence 3 of the [SemnaticKitti](http://semantic-kitti.org/) dataset.
<p align="center">
<img src="https://github.com/anirudhtopiwala/OpenSource_Problems/blob/master/Spherical_View_Projection/assests/Sphereical_projection.gif">
</p>

A more clearer video can be found on YouTube [here](https://youtu.be/1vSI_j435Vs).

## Dependencies
To run this program you need to have the following installed on your system:
* [PCl](http://pointclouds.org/): To load and process the point cloud.
* [OpenCV](https://opencv.org/): To visualize the spherical projection image.

## Build Instructions

To build this code, run the following commands:
```
cd ~
git clone https://github.com/anirudhtopiwala/OpenSource_Problems.git
cd ~/OpenSource_Problems/Spherical_View_Projection/
mkdir build
cd build
cmake ..
make
```

## Running the node
To run the node
```
./spherical_node 
```
This wil show you the the spherical projection image formed from test_cloud.pcd present in the assests folder. To run your own file make sure to set the path correctly in the main() function.

## Generating Doxygen Documentation

To install doxygen run the following command:
```
sudo apt install doxygen
```
Now, to generate doxygen documentation, run the following commands:
```
cd ~/OpenSource_Problems/Spherical_View_Projection/
doxygen doxy_config
```
Doxygen files will be generated to /docs folder. To view them in a browser, run the following commands:
```
cd docs/html
firefox index.html
```

