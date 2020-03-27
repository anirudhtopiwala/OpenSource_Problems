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
#ifndef SPHERICAL_VIEW_PROJECTION_SPHERICAL_VIEW_PROJECTION_H_
#define SPHERICAL_VIEW_PROJECTION_SPHERICAL_VIEW_PROJECTION_H_

#include <pcl/point_types.h>  // For PCL different cloud types

#include <vector>

/**
 * @brief this wraps all the configurations needed for doing spherical
 * projection.
 *
 */
struct Configuration {
  /**
   * @brief The upper filed of view of the lidar (degrees)
   *
   */
  double fov_up = 0.0;
  /**
   * @brief The lower filed of view of the lidar (degrees)
   *
   */
  double fov_down = 0.0;
  /**
   * @brief The number of lasers in the lidar. This will make up the width of
   * the projection image.
   *
   */
  double num_lasers = 0.0;
  /**
   * @brief the length of the projection image.
   *
   */
  double img_length = 0.0;
};

class SphericalConversion {
 public:
  /**
   * @brief Constructor to initialize the configuration and the projection
   * image.
   *
   * @param[in] configurations to be set for the projection image
   */
  SphericalConversion(const Configuration& config);
  /**
   * @brief Loads the point cloud of type .pcd in the cloud_ class variable.
   *
   * @param[in] path Absolute path to the .pcd file
   * @return -1 The path is invalid
   * @return 1 Cloud Loaded Successfully
   */
  int LoadCloud(const std::string& path);
  /**
   * @brief Function to iterate over each point of cloud and make the projection
   * image.
   *
   * @return -1 The cloud is empty
   * @return 1 spherical image formed successfully
   */
  int MakeImage();
  /**
   * @brief Convert 3D point to 2D pixel cooredinated by doing Spherical
   * Projection
   *
   * @param[in] point
   * @param[in] fov_rad
   * @param[in] fov_down_rad
   * @param[out] pixel_x
   * @param[out] pixel_y
   * @param[out] depth
   *
   */
  void GetProjection(const pcl::PointXYZI& point, const double& fov_rad,
                     const double& fov_down_rad, int* pixel_x, int* pixel_y,
                     double* depth) const;
  /**
   * @brief function to return the spherical image
   *
   * @return auto
   */
  auto GetImg() const;
  /**
   * @brief Use OpenCv to view the spherical image formed
   *
   * @param img
   */
  void ShowImg(const std::vector<std::vector<std::vector<double>>>& img) const;

 private:
  /**
   * @brief The configuration required for forming the spherical projection
   *
   */
  const Configuration config_;
  /**
   * @brief this will hold the projected image
   *
   */
  std::vector<std::vector<std::vector<double>>> spherical_img_;
  /**
   * @brief the point cloud will be loaded and accesible to the class through
   * this variable.
   *
   */
  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_;
};

#endif  // SPHERICAL_VIEW_PROJECTION_SPHERICAL_VIEW_PROJECTION_H_
