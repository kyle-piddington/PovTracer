#include "scene/Scene.hpp"
#include "povray/PovParser.hpp"
#include "window/ImageWriter.hpp"
#include "render/Renderer.hpp"
#include <iostream>
#include <fstream>
int main(int argC, char ** argV)
{
   //./raytrace wdth ht povray
   //
   std::shared_ptr<IWindow> window = std::make_shared<ImageWriter>();
   std::shared_ptr<Scene> scene = nullptr;

   int width, height;
   if(argC < 4)
   {
      std::cout << "raytrace <width> <height> <input_file> " << window->flags();
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
   Renderer renderer(width, height, scene);
   for(int j = 0; j < height; j++)
   {
      for(int i = 0; i < width; i++)
      {
         window->set_pixel(i,j,renderer.cast(i,j));
      }
   }
   if(window->shutdown())
   {
      return -1;
   }
   return 0;


}