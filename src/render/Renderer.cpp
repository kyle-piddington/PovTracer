#include "render/Renderer.hpp"

Renderer::Renderer(int imgw, int imgh, std::shared_ptr<Scene> scene):
width(imgw),
height(imgh),
scenePtr(scene),
sceneCam(scene->getCamera())
{

}

Renderer::~Renderer()
{
   shutdown();
}

Ray Renderer::getRayForPx(int px, int py)
{
   Amount ux = (px + 0.5)/width - 0.5;
   Amount uy = (py + 0.5)/height - 0.5;
   return scenePtr->getCamera().getRay(ux, uy);
}

Color4 Renderer::cast(int px, int py)
{
   Hit hit = scenePtr->trace(getRayForPx(px, py));
   if(hit.didHit())
   {
      return shade(hit);
   }
   else
   {
      return scenePtr->getBackgroundColor();
   }
}

Color4 Renderer::shade(Hit & hit)
{
   return hit.getGeometry()->getPigment()->getColor(hit);
}

void Renderer::init()
{

}

void Renderer::shutdown()
{

}