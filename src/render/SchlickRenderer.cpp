#include "render/SchlickRenderer.hpp"
#include "math/Maths.hpp"
#include <cassert>
/**
 * @TODO: Internal reflection bugs.
 * Spheres2.pov is currently rendering
 * incorrectly due to how refraction handles the weird edge case
 * of entering and exiting. really, the best solution is.....
 */
SchlickRenderer::SchlickRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular,
         Amount kDepth):
   Renderer(imgw,imgh,scene),
   diffuseBrdf(diffuse),
   specularBrdf(specular),
   lights(scene->getLights()),
   kDepth(kDepth)
   {

   }

SchlickRenderer::ColorInfo SchlickRenderer::calculateDiffuseSpec(Hit & hit)
{
   Color4 pigmentColor = hit.getGeometry()->getPigment()->getColor(hit);
   Finish * finish = hit.getGeometry()->getFinish();
   ColorInfo info;
   info.amb = finish->getAmbient() * pigmentColor;
   Vector3 wr = (sceneCam.getLocation() - hit.getHitpoint()).normalized();
   for (std::vector<const PointLight>::iterator pLight = lights.begin(); pLight != lights.end(); ++pLight)
   {
      //Shadowfeeler hit
      Vector3 lightDir = (pLight->getPosition() - hit.getHitpoint());
      Ray shadowRay(hit.getHitpoint() + hit.getNormal()*kEpsilon,lightDir);
      Hit shadowRes = scenePtr->trace(shadowRay);
      //If T  > 1.0
      Color4 diffuseColor, specularColor;
      diffuseColor.setZero();
      specularColor.setZero();

      if(!shadowRes.didHit()||shadowRes.getDistance() > lightDir.norm())
      {
         Vector3 wi = lightDir.normalized();
         Amount diffuse =  diffuseBrdf->eval(wi, wr, hit);
         Amount specular = specularBrdf->eval(wi, wr, hit);
         diffuseColor = diffuse * pigmentColor.cwiseProduct(pLight->getColor());
         //Specular color of surface assumed to be (1,1,1)
         specularColor = pLight->getColor() * specular;
      }
      info.diff = diffuseColor;
      info.spec = specularColor;
   }
   return info;
}

Color4 SchlickRenderer::calculateReflection(Hit & hit)
{
   //Calcualte reflection directionp
   const Ray & r = hit.getRay();
   Vector3 nextDir = r.direction.normalized() - 2 * r.direction.normalized().dot(hit.getNormal())*hit.getNormal();
   Ray next(hit.getHitpoint() + nextDir * kEpsilon, nextDir);
   //Increment iteration
   next.iter = r.iter + 1;
   //Recursive call
   next.type = Ray::REFLECTION;
   return this->shadeRay(next);
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
   return shadeRay(refrRay);

}

Amount calculateShlicks(Amount iorA, Amount iorB, const Vector3 & rI, Vector3 n)
{
   Amount angle = (-rI).normalized().dot(n.normalized());
   
   if(iorA > iorB)
   {
      Amount s2Theta = pow(sin(acos(angle)),2);
      if(fabs(s2Theta - 1) < kEpsilon)
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
   logger->logRay(hit.getRay(),hit,diffSpecInfo.amb.segment<3>(0),
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

         return schlicks*refl + (1-schlicks)*refr + diffSpecInfo.spec;
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