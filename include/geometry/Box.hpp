#pragma once
#include "Precision.hpp"
#include "IGeometry.hpp"
class Box : public IGeometry
{
public:
   Box();
   Box(Vector3 min, Vector3 max);
   void setMinCoords(Vector3 minCoords);
   void setMaxCoords(Vector3 maxCoords);
   virtual Hit intersect(const Ray & ray, Amount closestT);

private:
   virtual BoundingBox createUntransformedBoundingBox() const;
   Vector3 minCoords, maxCoords;

};
