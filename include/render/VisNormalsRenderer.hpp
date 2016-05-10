#pragma once
#include "render/Renderer.hpp"
class VisNormalsRenderer : public Renderer
{
public:
   VisNormalsRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene);
   Color4 shade(Hit & hit);
};
