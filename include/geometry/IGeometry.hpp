#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include "Precision.hpp"
#include "base/Hit.hpp"
#include "base/Ray.hpp"

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
   virtual Color4 shade(const Hit & hit) = 0;
   virtual Hit intersect(const Ray & ray) = 0;

};
#endif