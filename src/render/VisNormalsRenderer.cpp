#include "render/VisNormalsRenderer.hpp"

VisNormalsRenderer::VisNormalsRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene):
   Renderer(imgw, imgh, scene)
{

}
Color4 VisNormalsRenderer::shade(Hit & hit)
{
   Color4 col;
   col << hit.getNormal()*0.5 + Color3(0.5,0.5,0.5), 0;
   return col;
}
