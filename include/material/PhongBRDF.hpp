#ifndef __PHONG_BRDF_H__
#define __PHONG_BRDF_H__
#include "material/BRDF.hpp"
/** 
 * The Phong BRDF is a very
 * simple approximation of a full BRDF,
 * but contains enough information to light a scene.
 */
struct PhongDiffuseBRDF : public BRDF{
   Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit);
};
struct PhongSpecularBRDF : public BRDF{
   Amount eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit);
};
#endif