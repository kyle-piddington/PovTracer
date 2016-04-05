#include "math/Maths.hpp"
#include <Eigen/Geometry>

Vector3 Maths::project(Vector3 v, Vector3 u)
{
   return (u.dot(v)/u.dot(u)) * u;
}

Quaternion Maths::quatFromEuler(Vector3 euler)
{
  
   return AngleAxis<Amount>(euler[0], Vector3f::UnitZ())
          * AngleAxis<Amount>(euler[1], Vector3f::UnitY())
          * AngleAxis<Amount>(euler[2], Vector3f::UnitZ());

}