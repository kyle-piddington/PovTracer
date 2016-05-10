#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "scene/Scene.hpp"
#include "log/ILogger.hpp"
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
   Ray getRayForPx(Amount px, Amount py);


   virtual void init();

   virtual void shutdown();

   /**
    * Set a number of samples for this render
    * @param numSamples the number of samples to take.
    */
   virtual void setNSamples(int numSamples);

   /**
    * Shade a hit object. This method must be overloaded
    * in a renderer subclass
    * @param  hit the hit object to shade
    * @return     a color
    */
   virtual Color4 shade(Hit & hit) = 0;

   Color4 cast(int px, int py);

   /**
    * Provide a new logger to the renderer
    * @param logger the new logger.
    */
   void provideLogger(std::shared_ptr<ILogger> logger);

private:

   Color4 shadePixel(Amount px, Amount py);
   int comp = 3;
   int width;
   int height;
   int N_SAMPLES;
protected:
   //Logging method, px and py are more or less just for logging.
   Color4 shadeRay(Ray & ray, int px, int py);
   Color4 shadeRay(Ray & ray);
   std::shared_ptr<Scene> scenePtr;
   const Camera & sceneCam;
   std::shared_ptr<ILogger> logger;

};
#endif