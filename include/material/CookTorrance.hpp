#pragma once 
#include "material/BRDF.hpp"
#include "material/Beckmann.hpp"
/** 
 * Cook torrance BRDF!
 */
struct CookTorrance : public BRDF{
   Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit);
private:
   Beckmann beckmannDistribution;
};
