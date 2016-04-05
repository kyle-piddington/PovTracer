#ifndef __HIT_H__
#define __HIT_H__
#include <memory>
/**
 * A Hit represents a collision event between some geometry and 
 * a ray. Hit events are generated with a pointer to the object they hit,
 * the ray that caused the intersection.
 */
class IGeometry;
class Ray;

class Hit
{
public:
   Hit();
private:
   std::shared_ptr<Ray>       ray;
   std::shared_ptr<IGeometry> object;
   bool hitGeometry;

};
#endif