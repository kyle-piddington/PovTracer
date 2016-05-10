
#include "window/ImageWriter.hpp"
#include "util/StbImageWriter.hpp"
#include <iostream>
//Optional Arguments: Output file name.
// ./raytrace wdt ht, filename
int ImageWriter::init(int argC, char ** argV)
{
   outName = "out.png";

   width = atoi(argV[1]);
   height = atoi(argV[2]);
   if(argC >= 6)
   {
      outName = argV[argC-1];
   }
   buffer.resize(comp * width *height);
   return 0;
}

void ImageWriter::set_pixel(int x, int y, const Color4 & color)
{
   float yFlipped = (height - y - 1);
   if(x >= 0 && x < width && yFlipped >= 0 && yFlipped < height)
   {
      buffer[3*(yFlipped * width + x)] =     (int)255 * fmin(color.x(),1.0);
      buffer[3*(yFlipped * width + x) + 1] = (int)255 * fmin(color.y(),1.0);
      buffer[3*(yFlipped * width + x) + 2] = (int)255 * fmin(color.z(),1.0);
   }
   else
   {
      std::cout << x << "," << yFlipped << " is out of bounds" << std::endl;
   }
}

int ImageWriter::shutdown()
{
   int stride_in_bytes = width*comp*sizeof(unsigned char);
   return stbi_write_png(outName.c_str(),width,height,3,&buffer[0],width*3*sizeof(char));
}

std::string ImageWriter::flags()
{
   return "[output_filename]";
}