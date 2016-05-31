#pragma once

#include "render/SchlickRenderer.hpp"
#include "material/PhongBRDF.hpp"
#include "material/BRDF.hpp"
/**
 * Renders a brdf using a single cast
 * approximation for the light.
 */
class MonteCarloRenderer : public SchlickRenderer
{
public:
   
   MonteCarloRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular,
         int kDepth, int giDepth, int nSamples);
   Color4 shade(Hit & hit) override;
  
protected:
   ReflectRefractRenderer::ColorInfo calculateDiffuseSpec(Hit & hit) override;
   Color4 calculateIndirectLighting(Hit & hit);
   /**
    * Generate a centered hemisphere sample oriented
    * along a normal.
    * @param  nor The normal
    * @return     a sample point
    */
   int kGiDepth;
   int kNSamples;
};
