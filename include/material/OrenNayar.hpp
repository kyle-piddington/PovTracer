#pragma once
#include "material/BRDF.hpp"
/** 
 * Oren-Nayar approximation of the diffuse
 * term of the BRDF.
 */
struct OrenNayar : public BRDF{
   Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit);
};
