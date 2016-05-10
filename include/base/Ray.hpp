#ifndef __RAY_H__
#define __RAY_H__
#include "Precision.hpp"
/**
 * A ray is an infinite line that 
 * can instersect with Geometry objects.
 */
struct Ray
{
   Ray();
   Ray(Vector3 orig, Vector3 dir);
   Ray(const Ray & other);
   Ray & operator=(const Ray &rhs);
   Vector3 origin;
   Vector3 direction;
   Amount ior;
   Amount iter;
   /**
    * Get the position of the ray at time t
    * @param  t the time of impact
    * @return   the position at the time.
    */
   Vector3 at(Amount t) const;

   friend std::ostream& operator<<(std::ostream& os, const Ray& ray);

};
#endif