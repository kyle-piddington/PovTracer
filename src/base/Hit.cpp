#include "base/Hit.hpp"
#include "geometry/IGeometry.hpp"
#include "base/Ray.hpp"

Hit::Hit(const Ray & ray):
   ray(ray),
   object(nullptr),
   hitGeometry(false),
   normal(Vector3(0,0,0)),
   hPoint(ray.origin)
{

}

Hit::Hit(const Ray & ray, IGeometry * obj, const Vector3 & normal, Amount t):
   ray(ray),
   object(obj),
   hPoint(ray.origin + ray.direction * t),
   normal(normal),
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

Vector3 Hit::getNormal() const
{
   return normal;
}

IGeometry * Hit::getGeometry() const
{
   return object;
}

bool Hit::didHit() const
{
   return hitGeometry;
}

void Hit::setScene(Scene * scene)
{
   this->scene = scene;
}

Scene * Hit::getScene() const
{
   return this->scene;
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