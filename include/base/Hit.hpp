#ifndef __HIT_H__
#define __HIT_H__
#include "Geometry/IGeometry.hpp"

/**
 * A Hit represents a collision event between some geometry and 
 * a ray. Hit events are generated with a pointer to the object they hit,
 * the ray that caused the intersection. 
 */
class Hit
{
   std::weak_ptr<Ray>       ray;
   std::weak_ptr<IGeometry> object;
   bool hitGeometry

};
#endif