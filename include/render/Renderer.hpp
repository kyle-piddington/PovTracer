#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "scene/Scene.hpp"
class Renderer
{
public:
   Renderer(int imgw, int imgh, std::shared_ptr<Scene> scene);
   /**
    * Get the ray for a given pixel, with 0,0 being the
    * top left pixel
    * @param  px the x-pixel, between 0 and image width
    * @param  py the y-pixel, between 0 and image height
    * @return    A ray
    */
   Ray getRayForPx(int px, int py);

private:
   int width;
   int height;
   std::shared_ptr<Scene> scenePtr;

};
#endif