#include "render/SchlickRenderer.hpp"
#include "math/Maths.hpp"
#include <cassert>


SchlickRenderer::SchlickRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular,
         Amount kDepth):
   ReflectRefractRenderer(imgw, imgh, scene, diffuse, specular, kDepth)
   {

   }
Amount calculateShlicks(Amount iorA, Amount iorB, const Vector3 & rI, Vector3 n)
{
   Amount angle = (-rI).normalized().dot(n.normalized());
   if(iorA > iorB)
   {
      Amount iorRatio = iorA/iorB;
      const Amount s2Theta  = iorRatio * iorRatio * (1.0 - angle * angle);
      if(s2Theta > 1)
      {
         return 1;
      }
      angle = sqrt(1-s2Theta);
   }

   Amount R0 = pow((iorA - iorB)/(iorA + iorB),2);
   return R0 + (1 - R0)*pow(1 - angle,5);


}

Color4 SchlickRenderer::shade(Hit & hit)
{
   const Ray & r = hit.getRay();
   bool internal = false;
   if(r.direction.dot(hit.getNormal()) >= 0)
   {

      internal = true;
      hit.flipNormal();
   }
   Finish * finish = hit.getGeometry()->getFinish();
   ColorInfo diffSpecInfo = calculateDiffuseSpec(hit);
   Color4 diffSpec = diffSpecInfo.amb + diffSpecInfo.diff + diffSpecInfo.spec;
   logger->logRay(hit,diffSpecInfo.amb.segment<3>(0),
                                   diffSpecInfo.diff.segment<3>(0),
                                   diffSpecInfo.spec.segment<3>(0));

   diffSpec.w() = hit.getGeometry()->getPigment()->getColor(hit)(3);
   if(hit.getRay().iter < kDepth && (finish->getReflection() > kEpsilon || finish->getRefraction()))
   {
      Color4 refl;
      refl = calculateReflection(hit);
      if(finish->getRefraction())
      {
         //Determine ior
         Amount iorA = 1.0;
         Amount iorB = finish->getIor();
         if(internal)
         {
            Amount tmp = iorA;
            iorA = iorB;
            iorB = tmp;
         }
         Amount schlicks =  calculateShlicks(iorA, iorB, r.direction, hit.getNormal());
         Color4 refr = calculateRefraction(hit, internal);

         return schlicks*refl + (1-schlicks)*refr;// + diffSpecInfo.spec;
      }
      else
      {
         return (1 - finish->getReflection())*diffSpec + finish->getReflection()*refl;
      }
   }
   else
   {
      return diffSpec;
   }

}