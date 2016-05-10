#pragma once
#include "Precision.hpp"
#include "IGeometry.hpp"

class Triangle : public IGeometry
{
public:
   Triangle(Vector3 a, Vector3 b, Vector3 c);
   virtual Hit intersect(const Ray & ray, Amount closestT);

private:
   Vector3 vA, vB, vC;
   Vector3 normal;
};
