#include "render/Renderer.hpp"

Renderer::Renderer(int imgw, int imgh, std::shared_ptr<Scene> scene):
width(imgw),
height(imgh),
scenePtr(scene)
{

}

Ray Renderer::getRayForPx(int px, int py)
{
   Amount ux = (px + 0.5)/width - 0.5;
   Amount uy = (py + 0.5)/height - 0.5;
   return scenePtr->getCamera().getRay(ux, uy);
}