#ifndef __POVUTIL_H__
#define __POVUTIL_H__
#include <string>
#include <Eigen/Dense>
#include <sstream>
#include "Precision.hpp"
namespace PovUtil
{
   bool isComment(const std::string & comment);
   void processComment(std::istream & istream);
   Vector3 readVec3(std::istream & istream);
   Vector4 readVec4(std::istream & istream);

}
#endif
