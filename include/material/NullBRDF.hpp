#pragma once
#include "material/BRDF.hpp"
/** 
 * The Null brdf returns 0  for all wi and wr. Used for testing
 */
struct NullBRDF : public BRDF{
   Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit) { return 0; }
};
