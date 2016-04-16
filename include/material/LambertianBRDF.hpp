#pragma once 
#include "material/BRDF.hpp"
/** 
 * The Phong BRDF is a very
 * simple approximation of a full BRDF,
 * but contains enough information to light a scene.
 */
struct LambertianBRDF : public BRDF{
   Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit);
};
