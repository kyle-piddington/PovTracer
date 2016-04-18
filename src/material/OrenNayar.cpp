#include "material/OrenNayar.hpp"
#include "geometry/IGeometry.hpp"
#include "shade/Finish.hpp"
#include "math/Maths.hpp"
Amount OrenNayar::eval(const Vector3 & wi, const Vector3 & wr, const Hit & hit)
{
   /**
    * See https://en.wikipedia.org/wiki/Oren%E2%80%93Nayar_reflectance_model for the math
    * and http://ruh.li/GraphicsOrenNayar.html for the code!
    */
   Finish * finish = hit.getGeometry()->getFinish();
   Vector3 normal = hit.getNormal();
   Amount roughness = finish->getRoughness();
   Amount A = 1 - (0.5 * pow(roughness,2)) / (pow(roughness,2) + 0.57);
   Amount B = 0.45 * pow(roughness,2)/(pow(roughness,2) + 0.09);

   Amount thetaWi, thetaWr;
   thetaWi = acos(normal.dot(wi));
   thetaWr = acos(normal.dot(wr));
   //The difference (phiDiff) wi - wr can be found by dotting the projected vectors
   Amount gamma = ((wr - normal * wi.dot(normal))).dot(
                   (wi - normal * wr.dot(normal)));
   
   Amount alpha, beta;
   alpha = fmaxf(thetaWi,thetaWr);
   beta = fminf(thetaWi, thetaWr);
   
   return   finish->getDiffuse() * fmaxf(0.0,hit.getNormal().dot(wi)) *
               (A + (B * fmaxf(0,gamma) * sin(alpha) * tan(beta)));
}
