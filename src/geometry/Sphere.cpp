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
/**
 * For now, the shade returns a solid color
 */
Color4 Sphere::shade(const Hit & hit)
{
   return this->getPigment()->getColor(hit);
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
      Amount t = (-B - sqrt(det))/(2*A);
      if(t < kEpsilon)
      {
         return Hit(ray);
      }
      return Hit(ray, this, ray.origin + ray.direction * t);
   }
}