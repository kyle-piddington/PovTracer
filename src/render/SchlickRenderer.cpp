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


Color4 SchlickRenderer::calculateRefraction(Hit & hit, bool internal)
{
   //Create new ray
    
   Finish * finish = hit.getGeometry()->getFinish();
   const Ray & r = hit.getRay();
   Amount iorA = 1.0;
   Amount iorB = finish->getIor();
   Vector3 normal = hit.getNormal();
   if(internal)
   {
      Amount tmp = iorA;
      iorA = iorB;
      iorB = tmp;
   }

   Vector3 refractDir = Maths::refract(iorA,iorB,r.direction, normal);
   if(refractDir.norm() == 0)
   {
      return Color4(0,0,0,1);
   }
   Ray refrRay(hit.getHitpoint() + refractDir * kEpsilon, refractDir);
   refrRay.ior = finish->getIor();
   refrRay.iter = r.iter + 1;
   refrRay.type = Ray::REFRACTION;
   Hit refrHit = scenePtr->trace(refrRay);
   Color4 transColor;
   if(!refrHit.didHit())
   {
      transColor = scenePtr->getBackgroundColor();
   }
   else
   {
      transColor = shade(refrHit);
   }
   if(internal || !refrHit.didHit())
   {
      return transColor;
   }
   else
   {
      Color4 transparency;
      Color4 absorption = 0.1*hit.getGeometry()->getPigment()->getColor(hit);
      Amount dist = (hit.getHitpoint() - refrHit.getHitpoint()).norm();
      //Beers time!
      for(int i = 0; i < 3; i++)
      {
         transparency(i) = transparency(i)*exp(-dist*absorption(i));
      }
      transparency(3) = 1;

      return transColor.cwiseProduct(transparency);
   }

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
         Amount schlicks =  Maths::calculateShlicks(iorA, iorB, r.direction, hit.getNormal());
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