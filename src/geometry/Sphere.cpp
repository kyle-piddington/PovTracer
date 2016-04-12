#include "geometry/Sphere.hpp"
#include <iostream>
Sphere::Sphere():
   pos(Vector3(0.0,0.0,0.0)),
   rad(1.0)
{

}
Sphere::Sphere(Vector3 position, Amount radius):
   pos(position),
   rad(radius)
{

}

void Sphere::setPosition(Vector3 position)
{
   pos = position;
}

void Sphere::setRadius(Amount radius)
{
   rad = radius;
}


Hit Sphere::intersect(const Ray & ray)
{
   //Check ray determinent
   Amount A, B, C;
   A =  (ray.direction.dot(ray.direction));
   B =  2*(ray.origin - pos).dot(ray.direction);
   C =  (ray.origin - pos).dot(ray.origin - pos) - rad*rad;
   Amount det = B*B - 4*A*C;
   
   if(det < 0)
   {
      return Hit(ray);
   }
   else
   {
      Amount sqDet = sqrt(det);
      Amount t1 = (-B - sqDet)/(2*A);
      Amount t2 = (-B + sqDet)/(2*A);
      Amount t = std::min(t1,t2);
      if(t < 0)
      {
         t = std::max(t1,t2);
      }
      if(t < kEpsilon)
      {
         return Hit(ray);
      }
      Vector3 normal = (ray.at(t) - pos).normalized();
      return Hit(ray, this, normal,  t);
   }
}