#ifndef __Sphere_H__
#define __Sphere_H__
#include "Precision.hpp"
#include "IGeometry.hpp"
class Sphere : public IGeometry
{
public:
   Sphere();
   Sphere(Vector3 position, Amount radius);

   void setPosition(Vector3 position);
   void setRadius(Amount radius);

   virtual Hit intersect(const Ray & ray, Amount bestT);

private:
   Vector3 pos;
   Amount rad;
};
#endif