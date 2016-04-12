#include "render/PhongRenderer.hpp"

PhongRenderer::PhongRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene):
   Renderer(imgw,imgh,scene),
   lights(scene->getLights())
   {

   }

Color4 PhongRenderer::shade(Hit & hit)
{

   Color4 pigmentColor = hit.getGeometry()->getPigment()->getColor(hit);
   Finish * finish = hit.getGeometry()->getFinish();
   Color4 endRes;
   endRes = finish->getAmbient() * pigmentColor;
   Vector3 wr = sceneCam.getLocation() - hit.getHitpoint();
   for (std::vector<const PointLight>::iterator pLight = lights.begin(); pLight != lights.end(); ++pLight)
   {
      //Shadowfeeler hit
      Vector3 wi = (pLight->getPosition() - hit.getHitpoint());
      Ray shadowRay(hit.getHitpoint() + hit.getNormal()*kEpsilon,wi.normalized());
      Hit shadowRes = scenePtr->trace(shadowRay);

      if(!shadowRes.didHit()||shadowRes.getDistance() > wi.norm())
      {
         Amount diffuse =  diffuseBrdf.eval(wi, wr, hit);
         Amount specular = specularBrdf.eval(wi, wr, hit);
         endRes += diffuse * pigmentColor.cwiseProduct(pLight->getColor());
         endRes += pLight->getColor() * specular;
      }
   }
   endRes.w() = pigmentColor.w();
   return endRes;

}