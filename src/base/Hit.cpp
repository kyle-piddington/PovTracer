#include "base/Hit.hpp"
#include "geometry/IGeometry.hpp"
#include "base/Ray.hpp"

Hit::Hit(Ray ray):
   ray(ray),
   object(nullptr),
   hitGeometry(false),
   hPoint(ray.origin)
{

}

Hit::Hit(Ray ray, IGeometry * obj, Amount t):
   ray(ray),
   object(obj),
   hPoint(ray.origin + ray.direction * t),
   hitGeometry(true)
{

}

Amount Hit::getDistance() const
{
   if(!hitGeometry)
   {
      return -1;
   }
   else
   {
      return (hPoint - ray.origin).norm();
   }
}

const Ray & Hit::getRay()
{
   return ray;
}

Vector3 Hit::getHitpoint() const
{
   return hPoint;
}

IGeometry * Hit::getGeometry()
{
   return object;
}

bool Hit::didHit() const
{
   return hitGeometry;
}

std::ostream& operator<<(std::ostream& os, const Hit& hit)
{
   if(hit.didHit())
   {
      os << "hit position " << hit.getHitpoint().transpose() << " :  t = " << hit.getDistance();
   }
   else
   {
      os << "Hit: No Intersection";
   }
   return os;
}