#include "material/Beckmann.hpp"
#include "shade/Finish.hpp"
#include "geometry/IGeometry.hpp"

Amount Beckmann::eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit)
{
   Vector3 halfway = (wi + wr).normalized();
   Finish * finish = hit.getGeometry()->getFinish();

   Amount alpha = (hit.getNormal().dot(halfway));
   Amount numerator = exp((pow(alpha,2) - 1)/(pow(alpha,2)*pow(finish->getRoughness(),2)));
   Amount denominator = M_PI * pow(finish->getRoughness(),2) * pow(alpha,4);
   return numerator/denominator;
}