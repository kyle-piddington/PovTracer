#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
/**
 * The IGeometry interface is used by the Raytracer
 * to intersect rays with objects
 */
class IGeometry
{
   virtual void shade(const Hit & hit) = 0;
   virtual Hit intersect(const Ray & ray) = 0;

};
#endif