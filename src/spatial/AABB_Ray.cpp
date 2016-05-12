#include "spatial/AABB_Ray.hpp"
AABB_Ray::AABB_Ray(const Vector3 & origin, const Vector3 & dir):
   origin(origin)
{
   this->recipDir << 1/dir.x(), 1/dir.y(), 1/dir.z();
}
AABB_Ray::AABB_Ray(const Ray & ray):
   origin(ray.origin)
{
   this->recipDir << 1/ray.direction.x(), 1/ray.direction.y(), 1/ray.direction.z();
}
