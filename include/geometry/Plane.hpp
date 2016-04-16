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
   virtual Hit intersect(const Ray & ray);

private:
   Vector3 position;
   Vector3 orientation;

};
#endif