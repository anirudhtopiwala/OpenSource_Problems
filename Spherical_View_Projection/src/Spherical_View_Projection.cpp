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

#include "Spherical_View_Projection/Spherical_View_Projection.h"

#include <math.h>
#include <pcl/io/pcd_io.h>    // For Reading the Cloud
#include <pcl/point_cloud.h>  // For PCL Point Cloud
#include <pcl/point_types.h>  // For PCL different cloud types

#include <opencv2/opencv.hpp>  // For visualizing image
#include <vector>

SphericalConversion::SphericalConversion(const Configuration& config)
    : config_(config) {
    spherical_img_.assign(config_.num_lasers,
                          std::vector<std::vector<double>>(
                              config_.img_length, std::vector<double>(5, 0.0)));
    cloud_ = pcl::PointCloud<pcl::PointXYZI>::Ptr(
        new pcl::PointCloud<pcl::PointXYZI>);
};

int SphericalConversion::LoadCloud(const std::string& path) {
    // Loading from Bin File
    if (pcl::io::loadPCDFile<pcl::PointXYZI>(path, *cloud_) == -1) {
        std::cout << "Couldn't read the cloud file at: " << path << "\n";
        return -1;
    }
    return 1;
}
int SphericalConversion::MakeImage() {
    // Converting to Radians
    double fov_up_rad = (config_.fov_up / 180) * M_PI;
    double fov_down_rad = (config_.fov_down / 180) * M_PI;
    // Getting total Field of View
    double fov_rad = std::abs(fov_up_rad) + std::abs(fov_down_rad);
    if (cloud_->size() == 0) {
        std::cerr << "Empty Point Cloud_" << std::endl;
        return -1;
    }
    for (auto point : *cloud_) {
        // Getting Pixel from Point
        int pixel_v = 0;
        int pixel_u = 0;
        double range = 0.0;
        GetProjection(point, fov_rad, fov_down_rad, &pixel_v, &pixel_u, &range);
        spherical_img_.at(pixel_u).at(pixel_v) = std::vector<double>{
            point.x, point.y, point.z, range, point.intensity};
    }
    return 1;
}

void SphericalConversion::GetProjection(const pcl::PointXYZI& point,
                                        const double& fov_rad,
                                        const double& fov_down_rad,
                                        int* pixel_v, int* pixel_u,
                                        double* range) const {
    // range of Point from Lidar
    *range = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
    //  Getting the angle of all the Points
    auto yaw = atan2(point.y, point.x);
    auto pitch = asin(point.z / *range);
    // Get projections in image coords and normalizing
    double v = 0.5 * (yaw / M_PI + 1.0);
    double u = 1.0 - (pitch + std::abs(fov_down_rad)) / fov_rad;
    // Scaling as per the lidar config given
    v *= config_.img_length;
    u *= config_.num_lasers;
    // round and clamp for use as index
    v = floor(v);
    v = std::min(config_.img_length - 1, v);
    v = std::max(0.0, v);
    *pixel_v = int(v);

    u = floor(u);
    u = std::min(config_.num_lasers - 1, u);
    u = std::max(0.0, u);
    *pixel_u = int(u);
}

auto SphericalConversion::GetImg() const { return spherical_img_; }

void SphericalConversion::ShowImg(
    const std::vector<std::vector<std::vector<double>>>& img) const {
    cv::Mat sp_img(img.size(), img.at(0).size(), CV_64FC1);
    for (int i = 0; i < sp_img.rows; ++i) {
        for (int j = 0; j < sp_img.cols; ++j) {
            sp_img.at<double>(i, j) = img.at(i).at(j).at(4);  // Intensity value
        }
    }
    cv::imshow("Intensity Image", sp_img);
    cv::waitKey(0);
}

int main() {
    /** For Velodyne HDL 64-E
     * Fov_Up = 2 degrees
     * Fov_Down = -24.8 degrees
     * Num of Lasers = 64
     * Best length of image comes out to be = 1024
     */
    const Configuration config_input{2, -24.8, 64, 1024};
    const std::string path =
        "/home/" + std::string(getenv("USER")) +
        "/OpenSource_Problems/Spherical_View_Projection/assests/"
        "test_cloud.pcd";
    std::cout << path << std::endl;
    SphericalConversion conv(config_input);
    conv.LoadCloud(path);
    conv.MakeImage();
    auto img = conv.GetImg();
    conv.ShowImg(img);
}
