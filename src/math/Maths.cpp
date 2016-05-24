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
Amount Maths::randAmount(Amount lower, Amount upper)
{
  return ((float)rand()/INT_MAX)*(upper-lower) + lower;
}
Vector4 Maths::make_vec4(const Vector3 & vec3, Amount hCoord)
{
  Vector4 ret; ret<< vec3, hCoord;
  return ret;
}

Vector3 Maths::generateHemisphereSample(const Vector3 & normal, Amount focus)
{
  Amount r = pow(Maths::randAmount(0,1),1.0/focus);
  Amount theta = Maths::randAmount(0,2*M_PI);
  Amount x = cos(theta)*r;
  Amount y = sin(theta)*r;
  Vector3 sample; sample << x, y, sqrt(1 - (x*x + y*y));
  //Rotate sample
  Amount cosA = normal.dot(Vector3(0,0,1));
  Vector3 axis;
  if(fabs(cosA) > 1 - kEpsilon)
  {
    axis = normal;
  }
  else
  {
    axis = normal.cross(Vector3(0,0,1));
  }
  if(cosA < 0)
  {
    axis = -axis;
  }
  Vector3 rotSample = Eigen::AngleAxis<Amount>(acos(cosA),axis).matrix() * sample;
  return rotSample;
}

Amount Maths::calculateShlicks(Amount iorA, Amount iorB, const Vector3 & rI, Vector3 n)
{
   Amount angle = (-rI).normalized().dot(n.normalized());
   if(iorA > iorB)
   {
      Amount iorRatio = iorA/iorB;
      const Amount s2Theta  = iorRatio * iorRatio * (1.0 - angle * angle);
      if(s2Theta > 1)
      {
         return 1;
      }
      angle = sqrt(1-s2Theta);
   }

   Amount R0 = pow((iorA - iorB)/(iorA + iorB),2);
   return R0 + (1 - R0)*pow(1 - angle,5);
}