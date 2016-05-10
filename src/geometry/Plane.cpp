#include "geometry/Plane.hpp"


Plane::Plane():
   position(0,0,0),
   orientation(0,1,0)
{

}
Plane::Plane(Vector3 position, Vector3 orientation):
   position(position),
   orientation(orientation)
{

}
Plane::Plane(Vector3 orientation, Amount distance) :
   position(orientation*distance),
   orientation(orientation)
{

}

Hit Plane::intersect(const Ray & ray, Amount closestT)
{
   Amount rayDotN = ray.direction.dot(orientation);
   if(rayDotN == 0)
   {
      return Hit(ray);
   }
   else
   {
      Amount t = (this->position - ray.origin).dot(orientation)/
         rayDotN;
      if(t < 0)
      {
         return Hit(ray);
      }
      if(ray.direction.dot(orientation) > 0)
      {
         return Hit(ray, this, -orientation, t)
      }
      else
      {
         return Hit(ray, this, orientation, t);
      }
   }
}
