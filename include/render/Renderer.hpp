#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "scene/Scene.hpp"
class Renderer
{
public:
   Renderer(int imgw, int imgh, std::shared_ptr<Scene> scene);
   virtual ~Renderer();

   /**
    * Get the ray for a given pixel, with 0,0 being the
    * top left pixel
    * @param  px the x-pixel, between 0 and image width
    * @param  py the y-pixel, between 0 and image height
    * @return    A ray
    */
   Ray getRayForPx(int px, int py);

   virtual void init();

   virtual void shutdown();

   virtual Color4 shade(Hit & hit);

   Color4 cast(int px, int py);

private:
  int comp = 3;
   int width;
   int height;
   std::shared_ptr<Scene> scenePtr;
   const Camera & sceneCam;

};
#endif