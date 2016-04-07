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
   Vector3 origin;
   Vector3 direction;
};
#endif