#include "render/Renderer.hpp"
#include <random>
Renderer::Renderer(int imgw, int imgh, std::shared_ptr<Scene> scene):
width(imgw),
height(imgh),
scenePtr(scene),
sceneCam(scene->getCamera()),
N_SAMPLES(1)
{

}

Renderer::~Renderer()
{
   shutdown();
}

Ray Renderer::getRayForPx(Amount px, Amount py)
{
   Amount ux = (px + 0.5)/width - 0.5;
   Amount uy = (py + 0.5)/height - 0.5;
   return scenePtr->getCamera().getRay(ux, uy);
}

Color4 Renderer::shadePixel(Amount px, Amount py)
{
   Ray r = getRayForPx(px, py);
   std::cout << "Iteration type: Primary" << std::endl;
   Color4 rayColor =  shadeRay(r);
   #ifdef TEST_MODE
   {
      Color3 outColor; outColor << (int)rayColor(0)*255, (int)rayColor(1)*255, (int)rayColor(2)*255;
      std::cout << "Pixel:  [" << px << ", " << py << "] Ray : " << r << " T = " << hit.getDistance()
                << " Color: " << outColor.transpose() << std::endl;

   }
   #endif
   return rayColor;
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
      return shadePixel(px, py);
   }
   else
   {
      std::default_random_engine generator;
      std::uniform_int_distribution<Amount> distribution(-0.5,0.5/N_SAMPLES*N_SAMPLES);
      auto getSample = std::bind(distribution, generator);

      Color4 AAColor;
      AAColor.setZero();
   
      for(int i = 0; i < N_SAMPLES * N_SAMPLES; i++)
      {
         Amount xOff = (i%N_SAMPLES) / (Amount)N_SAMPLES + getSample();
         Amount yOff = (i/N_SAMPLES) / (Amount)N_SAMPLES + getSample();
         AAColor += shadePixel(px + xOff, py + yOff);
      }
      return AAColor / (N_SAMPLES * N_SAMPLES);
   }

}


void Renderer::init()
{

}

void Renderer::shutdown()
{

}