#pragma once
#include "Precision.hpp"
#include "base/Ray.hpp"


/**
 * A lightweight ray class for use in AABB calculations.
 */
struct AABB_Ray
{
   AABB_Ray(const Vector3 & origin, const Vector3 & dir);
   AABB_Ray(const Ray & ray);
   Vector3 origin;
   Vector3 recipDir;

};