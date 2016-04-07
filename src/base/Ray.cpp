#include "base/Ray.hpp"

Ray::Ray()
{
   
}
Ray::Ray(Vector3 o, Vector3 d):
   origin(o),
   direction(d)
   {

   }


std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
   os << "Position: " << ray.origin.transpose() << std::endl
      << "Direction: " << ray.direction.transpose();
   return os;
}