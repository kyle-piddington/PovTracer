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
   /**
    * Return a color from a shade
    * @param  hit [description]
    * @return     [description]
    */
   
    IGeometry();

   virtual Color4 shade(const Hit & hit) = 0;
   virtual Hit intersect(const Ray & ray) = 0;


   void setPigment(std::shared_ptr<IPigment> pigment);

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
   std::shared_ptr<IPigment> pigment;
   Finish finish;
};
#endif