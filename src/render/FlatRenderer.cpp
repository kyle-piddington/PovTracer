#include "render/FlatRenderer.hpp"

FlatRenderer::FlatRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene):
   Renderer(imgw, imgh, scene)
{

}
Color4 FlatRenderer::shade(Hit & hit)
{
   return hit.getGeometry()->getPigment()->getColor(hit);
}
