#ifndef __PLANE_H__
#define __PLANE_H__
#include "Precision.hpp"
#include "IGeometry.hpp"
class Plane : public IGeometry
{
public:
   Plane(Vector3 position, Vector3 orientation)
   virtual Color shade(const Hit & hit);
   virtual Hit intersect(const Ray & ray);

private:

};
#endif