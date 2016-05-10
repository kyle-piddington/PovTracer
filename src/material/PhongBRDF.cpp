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
   Amount n = 1.0/finish->getRoughness();
   Amount specular = finish->getSpecular() * pow(fmaxf(0.0,hit.getNormal().dot(halfway)),n);
   //Account for energy preservation (http://www.rorydriscoll.com/2009/01/25/energy-conservation-in-games/)
   return specular; //* (n + 8)/(8*M_PI);
}
