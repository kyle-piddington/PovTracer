#include "material/PhongBRDF.hpp"
#include "shade/Finish.hpp"
#include "geometry/IGeometry.hpp"

Amount PhongDiffuseBRDF::eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit)
{
   Finish * finish = hit.getGeometry()->getFinish();
   Amount diffuse = finish->getDiffuse() * fmaxf(0.0,hit.getNormal().dot(wi.normalized()));
   return diffuse;
}
Amount PhongSpecularBRDF::eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit)
{
   Vector3 halfway = (wi + wr).normalized();
   Finish * finish = hit.getGeometry()->getFinish();
   Amount specular = finish->getSpecular() * pow(fmaxf(0.0,hit.getNormal().dot(halfway)),1/finish->getRoughness());
   return specular;
}
