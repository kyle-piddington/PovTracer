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
class Scene;


class Hit
{
public:
   /**
    * Construct a 'missed' hit, a hit that did not hit a target
    */
   Hit(const Ray & ray);
   /**
    * Construct a hit that resulted from a successful raytrace
    */
   Hit(const Ray & ray,  IGeometry * obj, const Vector3 & normal, Amount t);
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
    * Get the t-value of the hit
    */
   const Amount getT() const;
   /**
    * Get the location of the intersection
    * @return the intersection
    */
   Vector3 getHitpoint() const;

   /**
    * Get the interescted object
    * @return the object this hit intersected with
    */
   IGeometry * getGeometry() const;

   /**
    * Set the scene this hit belongs to
    * @param  scene the scene
    */
   void setScene(Scene * scene);

   /**
    * Retreve the scene this belongs to.
    * @return the scene
    */
   Scene * getScene() const;

   /**
    * Retrieve the normal of this hit vector.
    * @return [description]
    */
   Vector3 getNormal() const;


   /**
    * Check to see if this hit actually was a hit
    * @return [description]
    */
   bool didHit() const;

   /**
    * Transform a hit using a transformation
    * matrix. 
    * @param transform    The Model transform to modify the hitpoint
    * @param invTranspose the inverse transpose of the transform matrix, to 
    *                     calculate the normal.
    */
   void transform(const Matrix4 & transform, const Matrix4 & invTranspose);

   friend std::ostream& operator<<(std::ostream& os, const Hit& hit);

private:
   Amount t;
   Vector3 hPoint;
   Vector3 normal;
   Ray  ray;
   IGeometry * object;
   Scene * scene;

   bool hitGeometry;

};
#endif