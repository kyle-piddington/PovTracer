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

   virtual Color4 shade(const Hit & hit);
   virtual Hit intersect(const Ray & ray);

private:
   Vector3 pos;
   Amount rad;
};
#endif