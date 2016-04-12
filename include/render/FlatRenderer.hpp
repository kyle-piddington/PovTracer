#ifndef __FLAT_RENDERER_H__
#define __FLAT_RENDERER_H__
#include "render/Renderer.hpp"
class FlatRenderer : public Renderer
{
public:
   FlatRenderer(int imgw, int imgh, std::shared_ptr<Scene> scene);
   Color4 shade(Hit & hit);
};
#endif