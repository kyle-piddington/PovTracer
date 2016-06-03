#include "shade/Texture.hpp"
#include "math/Maths.hpp"
#include "povray/ParseException.hpp"
#include <iostream>

Texture::Texture(int width, int height, int nComps, stbi_uc * buffer):
width(width),
height(height),
loaded(true),
nComps(nComps)
{
   this->buffer = new stbi_uc[width * height * nComps];
   std::memcpy(this->buffer,buffer,nComps*width*height*sizeof(stbi_uc));

}
Texture::Texture(std::string fileName, int reqComponents)
{
   FILE * file = fopen(fileName.c_str(), "r");
   if(file)
   {
      buffer = stbi_load_from_file(file,&width,&height,&nComps,reqComponents);
      loaded = true;
      fclose(file);
   }
   else
   {
      throw ParseException(fileName, "Unrecognized File: " + fileName);
   }
}

Texture::~Texture()
{
   if(buffer != nullptr)
   {
      delete buffer;
   }
}

Texture::Texture(const Texture & other):
   width(other.width),
   height(other.height),
   nComps(other.nComps),
   loaded(other.loaded)
{
   if(loaded)
   {
      delete buffer;

   }
   if(other.loaded)
   {
      buffer = new stbi_uc[other.width * other.height * nComps];
      std::memcpy(this->buffer,other.buffer,nComps*other.width*other.height*sizeof(stbi_uc));

   }

}

Texture &Texture::operator=(const Texture &other)
{
   if(&other == this)
   {
      return *this;
   }
   else
   {
      *this = Texture(other);
      return *this;
   }
}

Texture::Texture(Texture&& other):
   buffer(other.buffer),
   width(other.width),
   height(other.height),
   loaded(other.loaded)
{
   other.buffer = nullptr;
}

Texture & Texture::operator=(Texture&&other)
{
   if(&other == this)
   {
      return *this;
   }
   else
   {
      *this = Texture(other);
      return *this;
   }
}

int Texture::getWidth() const
{
   return width;
}
int Texture::getHeight() const
{
   return height;
}

Color3 Texture::sample(Vector2 uv) const
{
   assert(width > 0 && height > 0);
   if(loaded)
   {

      //Calculate Px coordinates.
      uv(0) = Maths::clamp(0,1-kEpsilon,uv(0));
      uv(1) = Maths::clamp(0,1-kEpsilon,uv(1));
      int pll_x = width *  (uv(0) - (0.5/width));
      int pll_y = height * (uv(1) -  (0.5/height));
      //Sample and weight 4 pixels;
      
      Color3 lowerLeft, lowerRight, upperLeft, upperRight;
      lowerLeft = readPixel(pll_x,pll_y);
      lowerRight = readPixel(pll_x + 1, pll_y);
      upperLeft = readPixel(pll_x, pll_y + 1);
      upperRight = readPixel(pll_x + 1, pll_y + 1);
      //Interpolate between the four.
      Amount interpX = uv(0) - (float)pll_x/width;
      Amount interpY = uv(1) - (float)pll_y/height;
      Color3 ret =
         lowerLeft * interpX * interpY + lowerRight * (1-interpX) * interpY +
         upperLeft * interpX * (1 - interpY) + upperRight * (1-interpX) * (1-interpY);
      return ret/255.0;
   }
   else
   {
      return Color3::Zero();
   }
}

Color3 Texture::readPixel(int x, int y) const
{  
   x = (int)Maths::clamp(0, width -1, x);
   y = (int)Maths::clamp(0, height-1, y);
   Color3 col; col << buffer[nComps * (x * height + y) + 0],
                      buffer[nComps * (x * height + y) + 1],
                      buffer[nComps * (x * height + y) + 2];
   return col;

}
