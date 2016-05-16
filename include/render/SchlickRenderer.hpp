#pragma once

#include "render/ReflectRefractRenderer.hpp"
#include "material/PhongBRDF.hpp"
#include "material/BRDF.hpp"
/**
 * Renders a brdf using a single cast
 * approximation for the light.
 */
class SchlickRenderer : public ReflectRefractRenderer
{
public:
   
   SchlickRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene,
         std::shared_ptr<BRDF> diffuse,
         std::shared_ptr<BRDF> specular,
         Amount kDepth);
   Color4 shade(Hit & hit);
  
};
