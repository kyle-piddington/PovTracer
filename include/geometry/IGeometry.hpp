#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include "Precision.hpp"
#include "base/Hit.hpp"
#include "base/Ray.hpp"
#include "shade/IPigment.hpp"
#include "shade/Finish.hpp"
/**
 * The IGeometry interface is used by the Raytracer
 * to intersect rays with objects
 */
class IGeometry
{
public:
    IGeometry();

   Hit intersectTransform(const Ray & ray, Amount closestT);
   virtual Hit intersect(const Ray & ray, Amount closestT) = 0;

   void setPigment(std::shared_ptr<IPigment> pigment);
   void setTransform(const Matrix4 & transform);
   /**
    * Get a reference to the pigment.
    */
   std::shared_ptr<IPigment>  getPigment();
   /**
    * Get a reference to the pigment pointer
    */
   std::shared_ptr<IPigment> * getPigmentPtr();
   
   Finish * getFinish();

   
private:
   bool transformed;
   Matrix4 transform, transformInv;
   std::shared_ptr<IPigment> pigment;
   Finish finish;
};
#endif