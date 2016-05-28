#include "geometry/Triangle.hpp"
#include "Precision.hpp"
#include "base/Hit.hpp"
Triangle::Triangle(Vector3 vA, Vector3 vB, Vector3 vC):
vA(vA),
vB(vB),
vC(vC)
{
   normal = (vB-vA).cross(vC-vA).normalized();
}

Hit Triangle::intersect(const Ray & ray, Amount closestT)
{
   /**
    * By applying Cramer's rule, we can solve a system
    * of three equations to determine the intersection of the traingle
    * | (a-b).x (a-c).x dx | |b| |ax - p0x|
    * | (a-b).y (a-c).y dy | |c| |ay - p0y|
    * | (a-b).z (a-c).z dz | |t| |az - p0z|
    *
    * | a b c | |beta|   |j|
    * | d e f | |gamma|  |k|
    * | g h i | |t|      |l|
    */
   //Local Variables

   //Implementation from http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
   Vector3 v0v1 = vB-vA;
   Vector3 v0v2 = vC-vA;
   Vector3 pVec = ray.direction.cross(v0v2);
   Amount det = v0v1.dot(pVec);
   /**
    * Triangle misses if det is zero.
    */
   if(std::abs(det) < kEpsilon)
   {
      return Hit(ray);
   }
   Amount invDet = 1 / det;
   Vector3 tVec = ray.origin - vA;
   //Solve for beta
   Amount beta = tVec.dot(pVec) * invDet;
   if(beta < 0 || beta > 1)
   {
      return Hit(ray);
   }
   //Solve for gamma
   Vector3 qVec = tVec.cross(v0v1);
   Amount gamma = ray.direction.dot(qVec) * invDet;
   //Check if hit
   if(gamma < 0 || beta + gamma > 1)
   {
      return Hit(ray);
   }

   Amount t = v0v2.dot(qVec) * invDet;
   //T should not be less than zero
   if(t < kEpsilon)
   {
      return Hit(ray);
   }

   return Hit(ray,this,this->normal,t);


   // Amount a, b, c, d, e, f, g, h, i, j, k, l;c

   // a = (vA-vB)(0);
   // d = (vA-vB)(1);
   // g = (vA-vB)(2);

   // b = (vA-vC)(0);
   // e = (vA-vC)(1);
   // h = (vA-vC)(2);

   // c = ray.direction(0);
   // f = ray.direction(1);
   // i = ray.direction(2);

   // j = (vA - ray.origin)(0);
   // k = (vA - ray.origin)(1);
   // l = (vA - ray.origin)(2);
   // //Det A:
   // Amount mtxDetRecip =  1.0/(a * (e * i - h * f) - b * (d * i - g * f) + c * (d * h - g * e));
   // Amount      t = (a * (e * l - h * k) - b * (d * l - g * k) + j * (d * h - g * e))*mtxDetRecip;
   // //Early bailout for closer objects
   // if( t > closestT && closestT > 0)
   // {
   //    return Hit(ray);
   // }
   // Amount beta =  (j * (e * i - h * f ) - b * (k * i - l * f) + c * (k * h - l * e))*mtxDetRecip;
   // //Early bailout for barycentric coordinates
   // if(-kEpsilon > beta || beta > 1 + kEpsilon)
   // {
   //    return Hit(ray);
   // }
   // Amount gamma = (a * (k * i - l * f) - j * (d * i - g * f) + c * (d * l - g * k))*mtxDetRecip;
   // if(-kEpsilon > gamma || gamma + beta > 1 + kEpsilon)
   // {
   //    return Hit(ray);
   // }

   //return Hit(ray, this, this->normal, t);
}


BoundingBox Triangle::createUntransformedBoundingBox() const
{
  Vector3 minCoords;
  Vector3 maxCoords;
  minCoords.x() = fmin(fmin(vB.x(),vC.x()),vA.x());
  minCoords.y() = fmin(fmin(vB.y(),vC.y()),vA.y());
  minCoords.z() = fmin(fmin(vB.z(),vC.z()),vA.z());
  maxCoords.x() = fmax(fmax(vB.x(),vC.x()),vA.x());
  maxCoords.y() = fmax(fmax(vB.y(),vC.y()),vA.y());
  maxCoords.z() = fmax(fmax(vB.z(),vC.z()),vA.z());
  //Add a bit of box for the bounding volume.
  for(int i=0; i < 3; i++)
  {
    if(fabs(minCoords(i) - maxCoords(i)) < kEpsilon)
    {
      minCoords(i) -= kEpsilon;
      maxCoords(i) += kEpsilon;
    }
  }
  return BoundingBox(minCoords, maxCoords);
}