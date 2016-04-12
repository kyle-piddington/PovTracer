#ifndef __Phong_RENDERER_H__
#define __Phong_RENDERER_H__
#include "render/Renderer.hpp"
#include "material/PhongBRDF.hpp"
class PhongRenderer : public Renderer
{
public:
   PhongRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene);
   Color4 shade(Hit & hit);
private:
   PhongDiffuseBRDF diffuseBrdf;
   PhongSpecularBRDF specularBrdf;
   const std::vector<PointLight> & lights;
};
#endif