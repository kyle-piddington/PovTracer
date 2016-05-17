#include "scene/Scene.hpp"
#include "povray/PovParser.hpp"
#include "window/ImageWriter.hpp"
#include <iostream>
#include <fstream>
#include "render/Renderer.hpp"
#include "render/FlatRenderer.hpp"
#include "render/SpecDiffuseBRDFRenderer.hpp"
#include "render/ReflectRefractRenderer.hpp"
#include "render/SchlickRenderer.hpp"
#include "render/VisNormalsRenderer.hpp"
#include "material/LambertianBRDF.hpp"
#include "material/PhongBRDF.hpp"
#include "material/CookTorrance.hpp"
#include "material/NullBRDF.hpp"
#include "material/OrenNayar.hpp"
#include "spatial/BVH.hpp"
#include <omp.h>
enum BRDFSwitch
{
   PHONG = 0,
   COOKTORRANCE = 1,
};

void printProgressBar(int amt, int total)
{
   int barWidth = 70;
   float progress = (float)amt/total;
   std::cout << "[";
   int pos = barWidth * progress;
   for (int i = 0; i < barWidth; ++i) {
      if (i < pos) std::cout << "=";
      else if (i == pos) std::cout << ">";
      else std::cout << " ";
   }
   std::cout << "] " << int(progress * 100.0) << " %\r";
   std::cout.flush();
}


int main(int argC, char ** argV)
{
   //./raytrace wdth ht povray
   //
   std::shared_ptr<IWindow> window = std::make_shared<ImageWriter>();
   std::shared_ptr<Scene> scene = nullptr;

   int width, height;
   if(argC < 4)
   {
      std::cout << "raytrace <width> <height> <input_file> <anti-aliasing>" << window->flags();
      return -1;
   }
   if(window->init(argC, argV))
   {
      return -1;
   }

   width = atoi(argV[1]);
   height = atoi(argV[2]);
   if(width <= 0 || height <= 0)
   {
      std::cout << "Width and height must be greater or equal to zero";
      return -1;
   }
   //load the povray file
   std::ifstream file;
   file.open(argV[3]);
   if(file.fail())
   {
      std::cout << "Could not open " << argV[3];
      return -1;
   }
   //Create the povscene.
   else
   {
      scene = PovParser::CreateScene(file);
   }
   file.close();
   bool aaSwitch = false;
   if(argC >= 5){
      aaSwitch = atoi(argV[4]);
   }

   //Choose renderer
   std::shared_ptr<Renderer> renderer;
   std::shared_ptr<BRDF> diffBRFD;
   std::shared_ptr<BRDF> specBRDF;
   specBRDF = std::make_shared<PhongSpecularBRDF>();
   diffBRFD = std::make_shared<LambertianBRDF>();

   
   //Add bvh
   scene->provideSpatialStructure(std::make_shared<BVH>());
   //renderer = std::make_shared<VisNormalsRenderer>(width,height,scene);
   renderer = std::make_shared<SchlickRenderer>(width, height, scene, diffBRFD, specBRDF,5);
   //Take 4x4 samples (16 per pixel)
   if(aaSwitch)
   {
      renderer->setNSamples(3);
   }
   else
   {
      renderer->setNSamples(1);   
   }
   int pxWritten = 0;
   #pragma omp parallel for
   for(int j = 0; j < height; j++)
   {
      int i = 0;
      for(i = 0; i < width; i++)
      {
         window->set_pixel(i,j,renderer->cast(i,j));

      }
      #pragma omp critical
      {
         pxWritten+=width;
         printProgressBar(pxWritten, width*height);

      }
   }
   if(window->shutdown())
   {
      return -1;
   }
   return 0;


}
