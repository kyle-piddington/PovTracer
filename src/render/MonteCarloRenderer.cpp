#include "render/MonteCarloRenderer.hpp"
#include "math/Maths.hpp"
#include <cassert>


MonteCarloRenderer::MonteCarloRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular,
         int kDepth,
         int giDepth, int nSamples ):
   SchlickRenderer(imgw, imgh, scene, diffuse, specular, kDepth),
   kGiDepth(giDepth),
   kNSamples(nSamples)
   {

   }


Color4 MonteCarloRenderer::calculateIndirectLighting(Hit & hit)
{
   if(hit.getRay().iter < kGiDepth)
   {
      //Sample and recurse
      Color4 collectedLight = Color4::Zero();
      Vector3 hitPoint = hit.getHitpoint();
      Ray hRay = hit.getRay();
      int nSamp = pow(kNSamples,1.0/(hRay.iter+1));
      std::vector<Vector3> samples;
      Maths::generateHemisphereSamples(hit.getNormal(),2,nSamp,&samples);
      for(int i = 0 ; i < nSamp; i++)
      {
         //Generate normal-centric samples
         Vector3 newDir = samples[i];
         Ray newRay(hitPoint + newDir * kEpsilon, newDir);
         newRay.iter = hRay.iter + 1;
         collectedLight += shadeRay(newRay);
      }
      collectedLight/= nSamp;
      return collectedLight;
   }
   else
   {
      return Color4::Zero();
   }
}


/**
 * Monte carlo doesn't actually have specular, use relflection instead.
 */
ReflectRefractRenderer::ColorInfo MonteCarloRenderer::calculateDiffuseSpec(Hit & hit)
{
   Color4 pigmentColor = hit.getGeometry()->getPigment()->getColor(hit);
   Finish * finish = hit.getGeometry()->getFinish();
   ColorInfo info;
   info.diff = Color4::Zero();
   info.spec = Color4::Zero();
   info.amb = calculateIndirectLighting(hit).cwiseProduct(pigmentColor);
   Vector3 wr = (sceneCam.getLocation() - hit.getHitpoint()).normalized();
   for (auto pLight = lights.begin(); pLight != lights.end(); ++pLight)
   {
      //Shadowfeeler hit
      Vector3 lightDir = (pLight->getPosition() - hit.getHitpoint());
      Ray shadowRay(hit.getHitpoint() + hit.getNormal()*kEpsilon,lightDir);
      Hit shadowRes = scenePtr->trace(shadowRay);
      //If T  > 1.0
      Color4 diffuseColor;
      diffuseColor = Color4::Zero();


      if(!shadowRes.didHit()||shadowRes.getDistance() > lightDir.norm())
      {
         Vector3 wi = lightDir.normalized();
         Amount diffuse =  diffuseBrdf->eval(wi, wr, hit);
         Amount specular = specularBrdf->eval(wi, wr, hit);
         diffuseColor = diffuse * pigmentColor.cwiseProduct(pLight->getColor());
         //Specular color of surface assumed to be (1,1,1)
      }
      info.diff += diffuseColor;
   }
   return info;
}


Color4 MonteCarloRenderer::shade(Hit & hit)
{
   const Ray & r = hit.getRay();
   bool internal = false;
   if(r.direction.dot(hit.getNormal()) >= 0)
   {
      internal = true;
      hit.flipNormal();
   }
   Finish * finish = hit.getGeometry()->getFinish();

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
         //@Todo: Add monte-carlo reflection
         //return Color4(0.0);
         ColorInfo diffSpecInfo = calculateDiffuseSpec(hit);
         Color4 diffSpec = diffSpecInfo.amb + diffSpecInfo.diff + diffSpecInfo.spec;

         logger->logRay(hit,          diffSpecInfo.amb.segment<3>(0),
                                      diffSpecInfo.diff.segment<3>(0),
                                      diffSpecInfo.spec.segment<3>(0));
         return (1 - finish->getReflection())*diffSpec + finish->getReflection()*refl;
      }
   }
   else
   {
      ColorInfo diffSpecInfo = calculateDiffuseSpec(hit);
      Color4 diffSpec = diffSpecInfo.amb + diffSpecInfo.diff + diffSpecInfo.spec;

      logger->logRay(hit,          diffSpecInfo.amb.segment<3>(0),
                                   diffSpecInfo.diff.segment<3>(0),
                                   diffSpecInfo.spec.segment<3>(0));
      return diffSpec;
   }

}
