#ifndef __POVUTIL_H__
#define __POVUTIL_H__
#include <string>
#include <Eigen/Dense>
#include <sstream>
#include "Precision.hpp"
namespace PovUtil
{
   bool isComment(const std::string & comment);
   Vector3 readVec3(std::stringstream & istream);
}
#endif
