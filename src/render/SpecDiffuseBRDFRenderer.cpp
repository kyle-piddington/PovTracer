#include "render/SpecDiffuseBRDFRenderer.hpp"

SpecDiffuseBRDFRenderer::SpecDiffuseBRDFRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular):
   Renderer(imgw,imgh,scene),
   diffuseBrdf(diffuse),
   specularBrdf(specular),
   lights(scene->getLights())
   {

   }

Color4 SpecDiffuseBRDFRenderer::shade(Hit & hit)
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
      if(!shadowRes.didHit()||shadowRes.getDistance() > lightDir.norm())
      {
         Vector3 wi = lightDir.normalized();
         Amount diffuse =  diffuseBrdf->eval(wi, wr, hit);
         Amount specular = specularBrdf->eval(wi, wr, hit);
         endRes += diffuse * pigmentColor.cwiseProduct(pLight->getColor());
         //Specular color of surface assumed to be (1,1,1)
         endRes += pLight->getColor() * specular;
      }
   }
   endRes.w() = pigmentColor.w();
   return endRes;

}