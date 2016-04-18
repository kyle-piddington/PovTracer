#include "scene/Scene.hpp"
#include "povray/PovParser.hpp"
#include "window/ImageWriter.hpp"
#include <iostream>
#include <fstream>
#include "render/Renderer.hpp"
#include "render/FlatRenderer.hpp"
#include "render/SpecDiffuseBRDFRenderer.hpp"
#include "material/LambertianBRDF.hpp"
#include "material/PhongBRDF.hpp"
#include "material/CookTorrance.hpp"
#include "material/NullBRDF.hpp"
#include "material/OrenNayar.hpp"
enum BRDFSwitch
{
   PHONG = 0,
   COOKTORRANCE = 1,
};
int main(int argC, char ** argV)
{
   //./raytrace wdth ht povray
   //
   std::shared_ptr<IWindow> window = std::make_shared<ImageWriter>();
   std::shared_ptr<Scene> scene = nullptr;

   int width, height;
   if(argC < 5)
   {
      std::cout << "raytrace <width> <height> <input_file> <BRDF Switch> " << window->flags();
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
   BRDFSwitch brdfswitch = (BRDFSwitch)atoi(argV[4]);
   //Choose renderer
   std::shared_ptr<Renderer> renderer;
   std::shared_ptr<BRDF> diffBRFD;
   std::shared_ptr<BRDF> specBRDF;
   switch(brdfswitch){
      case PHONG:
         specBRDF = std::make_shared<PhongSpecularBRDF>();
         diffBRFD = std::make_shared<LambertianBRDF>();

         break;
      case COOKTORRANCE:
         specBRDF = std::make_shared<PhongSpecularBRDF>();
         diffBRFD = std::make_shared<OrenNayar>();

         break;
      default:
         specBRDF = std::make_shared<NullBRDF>();
         diffBRFD = std::make_shared<NullBRDF>();
         break;
   }

   renderer = std::make_shared<SpecDiffuseBRDFRenderer>(width, height, scene, diffBRFD, specBRDF);
   //Take 4x4 samples (16 per pixel)
   renderer->setNSamples(4);
   for(int j = 0; j < height; j++)
   {
      for(int i = 0; i < width; i++)
      {
         window->set_pixel(i,j,renderer->cast(i,j));
      }
   }
   if(window->shutdown())
   {
      return -1;
   }
   return 0;


}