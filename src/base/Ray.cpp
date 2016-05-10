#include "base/Ray.hpp"

Ray::Ray():
origin(Vector3(0,0,0)),
direction(Vector3(0,0,0)),
ior(1.0),
iter(0)
{
   
}
Ray::Ray(Vector3 o, Vector3 d):
   origin(o),
   direction(d),
   ior(1.0),
   iter(0)
   {

   }

Vector3 Ray::at(Amount t) const
{
   return origin + t*direction;
}
std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
   os << "{ " << ray.origin.transpose() << " -> " << ray.direction.transpose() << "}";
   return os;
}