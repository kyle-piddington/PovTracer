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

Amount Maths::map(Amount aMin, Amount aMax, Amount bMin, Amount bMax, Amount value)
{
   return ((value - aMin)/(aMax-aMin))*(bMax - bMin) + bMin;
}

Matrix4 Maths::Matrix4_cast(const Quaternion & q)
{
   Matrix4 m;
   m.setIdentity();
   m.block<3,3>(0,0) = q.toRotationMatrix();
   return m;
}

Amount Maths::Fresnel0(Amount iorA, Amount iorB)
{
   return pow((iorA - iorB)/(iorA + iorB),2);
}


Vector3 Maths::refract(Amount iorA, Amount iorB, const Vector3  & incoming, const Vector3 & normal)
{
  Vector3 n = normal.normalized();
  Vector3 d  = incoming.normalized();
  const Amount iorRatio = iorA/iorB;
  const Amount cosD   = -(n.dot(d));
  const Amount sinT2  = iorRatio * iorRatio * (1.0 - cosD * cosD);
  if(sinT2 > 1.0)
  {
      return Vector3(0,0,0);
  }
  const Amount cosT = sqrt(1.0 - sinT2);
  return (iorRatio * d + (iorRatio * cosD - cosT) * n).normalized();
}