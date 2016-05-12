#include "render/Renderer.hpp"
#include <random>
#include <chrono>
#include "log/NulLLogger.hpp"
Renderer::Renderer(int imgw, int imgh, std::shared_ptr<Scene> scene):
width(imgw),
height(imgh),
scenePtr(scene),
sceneCam(scene->getCamera()),
logger(std::make_shared<NullLogger>()),
N_SAMPLES(1)
{

}

Renderer::~Renderer()
{
   shutdown();
}

Ray Renderer::getRayForPx(Amount px, Amount py)
{
   Amount ux = (px)/width - 0.5;
   Amount uy = (py)/height - 0.5;
   return scenePtr->getCamera().getRay(ux, uy);
}

Color4 Renderer::shadePixel(Amount px, Amount py)
{
   Ray r = getRayForPx(px, py);
   return shadeRay(r,px,py);

}

Color4 Renderer::shadeRay(Ray & ray, int px, int py)
{
   Hit hit = scenePtr->trace(ray);
   Color4 color;
   if(hit.didHit())
   {
      color = shade(hit);
   }
   else
   {
      color = scenePtr->getBackgroundColor();
   }
   logger->logPixel(px,py,ray,hit.getT(),color.segment<3>(0));
   return color;
}
Color4 Renderer::shadeRay(Ray & ray)
{
   Hit hit = scenePtr->trace(ray);
   if(hit.didHit())
   {
      return shade(hit);
   }
   else
   {
      Color3 zero; zero << 0,0,0;
      logger->logRay(hit.getRay(),hit,zero,zero,zero);
      return scenePtr->getBackgroundColor();
   }
}

void Renderer::setNSamples(int numSamples)
{
   this->N_SAMPLES = numSamples;
}

Color4 Renderer::cast(int px, int py)
{


   if(N_SAMPLES == 1)
   {
      return shadePixel(px+0.5, py+0.5);
   }
   else
   {
      //Create a seed:
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

      std::default_random_engine generator(seed);
      std::uniform_real_distribution<Amount> distribution(-0.5/N_SAMPLES,0.5/N_SAMPLES);
      auto getSample = std::bind(distribution, generator);

      Color4 AAColor;
      AAColor.setZero();

      for(int i = 0; i < N_SAMPLES * N_SAMPLES; i++)
      {
         Amount xOff = ((i%N_SAMPLES)+0.5) / (Amount)N_SAMPLES + getSample();
         Amount yOff = ((i/N_SAMPLES)+0.5) / (Amount)N_SAMPLES + getSample();
         AAColor += shadePixel(px + xOff, py + yOff);
  
      }
      return AAColor / (N_SAMPLES * N_SAMPLES);
   }

}

void Renderer::provideLogger(std::shared_ptr<ILogger> logger)
{
   this->logger = logger;
}

void Renderer::init()
{

}

void Renderer::shutdown()
{

}