#ifndef __PRECISION_HPP__
#define __PRECISION_HPP__
#include <Eigen/Dense>
#include <Eigen/Geometry>
/**
 * Precision.hpp contains several macros and defines to help
 * keep precision consistant throughout the application
 */
#define Vector3 Eigen::Vector3f
#define Vector4 Eigen::Vector4f

#define Color3 Eigen::Vector3f
#define Color4 Eigen::Vector4f

#define Matrix4 Eigen::Matrix4f
#define Quaternion  Eigen::Quaternionf
 
#define Amount float

#define kEpsilon 0.001

#endif