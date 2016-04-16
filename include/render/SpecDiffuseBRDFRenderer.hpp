#ifndef __Phong_RENDERER_H__
#define __Phong_RENDERER_H__
#include "render/Renderer.hpp"
#include "material/PhongBRDF.hpp"
#include "material/BRDF.hpp"
/**
 * Renders a brdf using a single cast
 * approximation for the light.
 */
class SpecDiffuseBRDFRenderer : public Renderer
{
public:
   SpecDiffuseBRDFRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular);
   Color4 shade(Hit & hit);
private:
   std::shared_ptr<BRDF> diffuseBrdf;
   std::shared_ptr<BRDF> specularBrdf;
   const std::vector<PointLight> & lights;
};
#endif