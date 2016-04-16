#include "material/LambertianBRDF.hpp"
#include "shade/Finish.hpp"
#include "geometry/IGeometry.hpp"

Amount LambertianBRDF::eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit)
{
   Finish * finish = hit.getGeometry()->getFinish();
   Amount diffuse = finish->getDiffuse() * fmaxf(0.0,hit.getNormal().dot(wi.normalized()));
   return diffuse;
}