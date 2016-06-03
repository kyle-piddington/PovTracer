#ifndef __PLANE_H__
#define __PLANE_H__
#include "Precision.hpp"
#include "IGeometry.hpp"
class Plane : public IGeometry
{
public:
   Plane();
   Plane(Vector3 position, Vector3 orientation);
   Plane(Vector3 orientation, Amount distance);
   virtual Hit intersect(const Ray & ray, Amount closestT);
   std::string getName() const{return "Plane";}
private:
   /**
    * Planes are a special case, with an infinite bounding box.
    * They will be kept outside of any acceleration structure, and traced after the fact.
    * @return [description]
    */
   virtual BoundingBox createUntransformedBoundingBox() const;
   Vector3 position;
   Vector3 orientation;

};
#endif