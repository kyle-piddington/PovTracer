#include "base/Ray.hpp"

Ray::Ray():
origin(Vector3(0,0,0)),
direction(Vector3(0,0,0)),
ior(1.0),
type(RayType::PRIMARY),
iter(0)
{
   
}
Ray::Ray(Vector3 o, Vector3 d):
   origin(o),
   direction(d),
   ior(1.0),
   type(RayType::PRIMARY),
   iter(0)
   {

   }

Ray::Ray(const Ray & other):
origin(other.origin),
direction(other.direction),
ior(other.ior),
iter(other.iter),
type(other.type)
{

}

Ray & Ray::operator=(const Ray &rhs){
   if(this == &rhs)
   {
      return *this;
   }
   else
   {
      this->origin = rhs.origin;
      this->direction = rhs.direction;
      this->ior = rhs.ior;
      this->iter = rhs.iter;
      this->type = rhs.type;
      return *this;
   }
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
