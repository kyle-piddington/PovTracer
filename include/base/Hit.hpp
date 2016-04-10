#ifndef __HIT_H__
#define __HIT_H__
#include <memory>
#include <iostream>
#include "base/Ray.hpp"
#include "Precision.hpp"
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
   /**
    * Construct a 'missed' hit, a hit that did not hit a target
    */
   Hit(Ray ray);
   /**
    * Construct a hit that resulted from a successful raytrace
    */
   Hit(Ray ray,  IGeometry * obj, Amount t);
   /**
    * Get the distance from the ray 
    * origin to the hit point
    * @return the distance, in units
    */
   Amount getDistance() const;
   /**
    * Get the original ray of this hit
    * @return the ray
    */
   const Ray & getRay();
   /**
    * Get the location of the intersection
    * @return the intersection
    */
   Vector3 getHitpoint() const;

   /**
    * Get the interescted object
    * @return the object this hit intersected with
    */
   IGeometry * getGeometry();

   /**
    * Check to see if this hit actually was a hit
    * @return [description]
    */
   bool didHit() const;

   friend std::ostream& operator<<(std::ostream& os, const Hit& hit);

private:

   Vector3 hPoint;
   Ray  ray;
   IGeometry * object;

   bool hitGeometry;

};
#endif