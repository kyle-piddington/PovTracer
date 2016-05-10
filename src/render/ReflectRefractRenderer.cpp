#include "render/ReflectRefractRenderer.hpp"
#include "math/Maths.hpp"
ReflectRefractRenderer::ReflectRefractRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
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

Color4 ReflectRefractRenderer::calculateDiffuseSpec(Hit & hit)
{
   Color4 pigmentColor = hit.getGeometry()->getPigment()->getColor(hit);
   Finish * finish = hit.getGeometry()->getFinish();
   Color4 endRes;
   endRes = finish->getAmbient() * pigmentColor;
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

      //Try a refractive bounce just in case

      if(!shadowRes.didHit()||shadowRes.getDistance() > lightDir.norm())
      {
         Vector3 wi = lightDir.normalized();
         Amount diffuse =  diffuseBrdf->eval(wi, wr, hit);
         Amount specular = specularBrdf->eval(wi, wr, hit);
         diffuseColor = diffuse * pigmentColor.cwiseProduct(pLight->getColor());
         //Specular color of surface assumed to be (1,1,1)
         specularColor = pLight->getColor() * specular;
      }
      #ifdef TEST_MODE
      std::cout << "Ambient: " << endRes.segment<3>(0).transpose()       << std::endl
                << "Diffuse: " << diffuseColor.segment<3>(0).transpose() << std::endl
                << "Specular " << specularColor.segment<3>(0).transpose() << std::endl;
      
      #endif

      endRes += diffuseColor + specularColor;

   }

   endRes.w() = pigmentColor.w();
   return endRes;
}

Color4 ReflectRefractRenderer::calculateReflection(Hit & hit)
{
   //Calcualte reflection directionp
   const Ray & r = hit.getRay();
   Vector3 nextDir = r.direction.normalized() - 2 * r.direction.normalized().dot(hit.getNormal())*hit.getNormal();
   Ray next(hit.getHitpoint() + nextDir * kEpsilon, nextDir);
   //Increment iteration
   next.iter = r.iter + 1;
   //Recursive call
   #ifdef TEST_MODE
   {
      std::cout << "Iteration type: Reflection" << std::endl;
   }
   #endif
   return this->shadeRay(next);
}


Color4 ReflectRefractRenderer::calculateRefraction(Hit & hit)
{
   //Create new ray
   
   Finish * finish = hit.getGeometry()->getFinish();
   const Ray & r = hit.getRay();
   Amount iorA = 1.0;
   Amount iorB = finish->getIor();
   Vector3 normal = hit.getNormal();
   if(r.direction.dot(normal) >= 0)
   {
      Amount tmp = iorA;
      iorA = iorB;
      iorB = tmp;
      normal = - normal;
   }
   Vector3 refractDir = Maths::refract(iorA,iorB,r.direction, normal);
   if(refractDir.norm() == 0)
   {
      return Color4(0,0,0,1);
   }
   Ray refrRay(hit.getHitpoint() + refractDir * kEpsilon, refractDir);
   refrRay.ior = finish->getIor();
   refrRay.iter = r.iter + 1;
   #ifdef TEST_MODE
   {
      std::cout << "Iteration type: Refraction" << std::endl;
   }
   #endif
   return shadeRay(refrRay);

}

Color4 ReflectRefractRenderer::shade(Hit & hit)
{
   #ifdef TEST_MODE
   {
      std::cout << hit.getRay() << std::endl;
   }
   #endif
   Finish * finish = hit.getGeometry()->getFinish();
   Color4 diffSpec = calculateDiffuseSpec(hit);
   Color4 resColor;
   #ifdef TEST_MODE
   {
      std::cout << "---------" << std::endl;
   }
   #endif
   if(hit.getRay().iter < kDepth && (finish->getReflection() > kEpsilon || finish->getRefraction()))
   {

      Color4 refl = calculateReflection(hit);
      if(finish->getRefraction())
      {
         Color4 refr = calculateRefraction(hit);
         Amount filter = hit.getGeometry()->getPigment()->getColor(hit)(3);
         return (1 - (finish->getReflection() + filter))*diffSpec + finish->getReflection()*refl + filter*refr;

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