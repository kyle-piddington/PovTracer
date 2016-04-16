#pragma once 
#include "material/BRDF.hpp"
/** 
 * BRDF modeling the beckmann distribution.
 * (See https://en.wikipedia.org/wiki/Specular_highlight#Beckmann_distribution)
 */
struct Beckmann : public BRDF{
   Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit);
};
