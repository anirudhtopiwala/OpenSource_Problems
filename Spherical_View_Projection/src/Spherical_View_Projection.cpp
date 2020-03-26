/*
 * MIT License
 * Copyright (c) 2020 Anirudh Topiwala
 * Author: Anirudh Topiwala
 * Create Date: 2020-03
 * Last Edit Date: 2020-03
 *
 * @brief This class is used to load a point cloud using pcl and convert it into
 * spherical view or front view projection. More information about the theory
 * can be found on the medium article here:
 *
 */

#include <math.h>
#include <pcl/io/pcd_io.h>    // For Reading the Cloud
#include <pcl/point_types.h>  // For PCL different cloud types

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "Spherical_View_Projection/Spherical_View_Projection.h"

#include <vector>

SphericalConversion::SphericalConversion(const Configuration& config)
    : config_(config) {
  sp_img_.assign(config_.num_lasers,
                 std::vector<std::vector<double>>(config_.img_length,
                                                  std::vector<double>(5, 0.0)));
  cloud_ =
      pcl::PointCloud<pcl::PointXYZI>::Ptr(new pcl::PointCloud<pcl::PointXYZI>);
};

int SphericalConversion::LoadCloud(const std::string& path) {
  // Loading from Bin File
  if (pcl::io::loadPCDFile<pcl::PointXYZI>(path, *cloud_) == -1) {
    std::cout << "Couldn't read the cloud file at: " << path << "\n";
    return -1;
  }
  return 1;
}
int SphericalConversion::MakeImage(){
  double fov_up_rad = (config_.fov_up / 180) * M_PI;
  double fov_down_rad = (config_.fov_down / 180) * M_PI;
  double fov_rad = std::abs(fov_up_rad) + std::abs(fov_down_rad);
  if (cloud_->size() == 0) {
    std::cerr << "Empty Point Cloud_" << std::endl;
    return -1;
  }
  for (size_t i = 0; i < cloud_->points.size(); ++i) {
    pcl::PointXYZI point = cloud_->points[i];
    // Getting Pixel from Point
    int pixel_x = 0;
    int pixel_y = 0;
    double depth = 0.0;
    GetProjection(point, fov_rad, fov_down_rad, &pixel_x, &pixel_y, &depth);
    std::vector<double> image_info_point{point.x, point.y, point.z, depth, point.intensity};
    sp_img_[pixel_y][pixel_x] = image_info_point;
  }
  return 1;
}

void SphericalConversion::GetProjection(const pcl::PointXYZI& point,
                                        const double& fov_rad,
                                        const double& fov_down_rad,
                                        int* pixel_x, int* pixel_y,
                                        double* depth) const {
  // Depth of Point from Lidar
  *depth = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
  //  Getting the angle of all the Points
  auto yaw = atan2(point.y, point.x);
  auto pitch = asin(point.z / *depth);
  // Get projections in image coords and scale to image size using
  // angular resolution
  double x = 0.5 * (yaw / M_PI + 1.0);
  double y = 1.0 - (pitch + std::abs(fov_down_rad)) / fov_rad;

  x *= config_.img_length;
  y *= config_.num_lasers;
  // round and clamp for use as index
  x = floor(x);
  x = std::min(config_.img_length - 1, x);
  x = std::max(0.0, x);
  *pixel_x = int(x);

  y = floor(y);
  y = std::min(config_.num_lasers - 1, y);
  y = std::max(0.0, y);
  *pixel_y = int(y);
}

auto SphericalConversion::GetImg() const { return sp_img_;}

void SphericalConversion::ShowImg(const std::vector<std::vector<std::vector<double>>>& img)const{
  cv::Mat sp_img(img.size(), img.at(0).size(), CV_64FC1);
  for (int i = 0; i < sp_img.rows; ++i) {
    for (int j = 0; j < sp_img.cols; ++j) {
      sp_img.at<double>(i, j) = img.at(i).at(j).at(4);

    }
  }
  cv::imshow("Intensity Image", sp_img);
  cv::waitKey(0);
}

int main() {
  // For Velodyne VLP 16
  const Configuration config_input{2, -20, 64, 1024};
  const std::string path = "/home/" + std::string(getenv("USER")) +
      "/OpenSource_Problems/Spherical_View_Projection/assests/"
      "test_pcd0.pcd";
std::cout<<path<<std::endl;
  SphericalConversion conv(config_input);
  conv.LoadCloud(path);
  conv.MakeImage();
  auto img = conv.GetImg();
  conv.ShowImg(img);
}
