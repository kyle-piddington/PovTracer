#ifndef __BRDF_H__
#define __BRDF_H__
#include "Precision.hpp"
#include "base/Hit.hpp"
/**
 * A Bidirectional Reflectance Distribution Function
 * is a function that evaluates the ratio of incoming radience, and outgoing irradience
 * of a material given an incoming light direction, an outgoing light direction,
 * and a hit.
 */
struct BRDF
{
   /**
    * Calculate the ratio between the outgoing and incoming light.   
    * @param  wi  the incoming light vector
    * @param  wr  the outgoing light vector
    * @param  hit The object containing infomration on the surface
    * @return     the ratio between radience and irradience.
    */
   virtual Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit) = 0;
};
#endif