#pragma once

#include "render/Renderer.hpp"
#include "material/PhongBRDF.hpp"
#include "material/BRDF.hpp"
/**
 * Renders a brdf using a single cast
 * approximation for the light.
 */
class ReflectRefractRenderer : public Renderer
{
public:
   ReflectRefractRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular,
         Amount kDepth);

   Color4 shade(Hit & hit);
private:
   Color4 calculateDiffuseSpec(Hit & hit);
   Color4 calculateReflection(Hit & hit);
   Color4 calculateRefraction(Hit & hit);
   Amount kDepth;
   std::shared_ptr<BRDF> diffuseBrdf;
   std::shared_ptr<BRDF> specularBrdf;
   const std::vector<PointLight> & lights;
};
