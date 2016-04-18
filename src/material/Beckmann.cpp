#include "material/Beckmann.hpp"
#include "shade/Finish.hpp"
#include "geometry/IGeometry.hpp"

//Credit to http://ruh.li/GraphicsCookTorrance.html fo the distribution calculation

Amount Beckmann::eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit)
{
   //
   Finish * finish = hit.getGeometry()->getFinish();
   Vector3 halfway = (wi + wr).normalized();
   Amount NdotH = (hit.getNormal().dot(halfway));

   Amount mSquared = pow(finish->getRoughness(),2);
   float r1 = 1.0 / ( 4.0 * mSquared * pow(NdotH, 4.0));
   float r2 = (NdotH * NdotH - 1.0) / (mSquared * NdotH * NdotH);
   return r1 * exp(r2);
}