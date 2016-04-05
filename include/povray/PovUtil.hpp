#ifndef __POVUTIL_H__
#define __POVUTIL_H__
#include <string>
#include <Eigen/Dense>
#include <sstream>
#include "Precision.hpp"
namespace PovUtil
{
   bool isComment(const std::string & comment);
   void processComment(std::stringstream & istream);
   Vector3 readVec3(std::stringstream & istream);
   Vector4 readVec4(std::stringstream & istream);
}
#endif
