#include "math/Maths.hpp"
#include <Eigen/Geometry>

Vector3 Maths::project(Vector3 v, Vector3 u)
{
   return (u.dot(v)/u.dot(u)) * u;
}

Quaternion Maths::quatFromEuler(Vector3 euler)
{
  
   return Eigen::AngleAxis<Amount>(euler[0], Vector3::UnitZ())
          * Eigen::AngleAxis<Amount>(euler[1], Vector3::UnitY())
          * Eigen::AngleAxis<Amount>(euler[2], Vector3::UnitZ());

}

Matrix4 Maths::Matrix4_cast(const Quaternion & q)
{
   Matrix4 m;
   m.setIdentity();
   m.block<3,3>(0,0) = q.toRotationMatrix();
   return m;
}