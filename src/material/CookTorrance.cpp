#include "material/CookTorrance.hpp"
#include "shade/Finish.hpp"
#include "geometry/IGeometry.hpp"

Amount CookTorrance::eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit)
{
   //Calulate D, F, and G
   Finish * finish = hit.getGeometry()->getFinish();
   Vector3 halfway = (wi + wr).normalized();
   Vector3 normal = hit.getNormal();
   Amount D = this->beckmannDistribution.eval(wi, wr, hit);
  

   Amount f0 = pow((1 - finish->getIor())/(1 + finish->getIor()),2);
 
   Amount F = f0 + (1 - f0)*pow(1 - wi.dot(halfway),5);
  
   Amount G = fmin(1, fmin(2 * normal.dot(halfway) * normal.dot(wr)/wr.dot(halfway),
                           2 * normal.dot(halfway) * normal.dot(wi)/wr.dot(halfway)));

   return D * F * G /(4 * normal.dot(wi) * normal.dot(wr));


}