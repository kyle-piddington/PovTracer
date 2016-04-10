#ifndef __IMAGE_WRITER_H__
#define __IMAGE_WRITER_H__ 
#include "IWindow.hpp"
#include <vector>
/**
 * ImageWriter is a simple window
 * that outputs a rendered image to a png file.
 */
class ImageWriter : public IWindow
{
    /**
    * Open and initialize the window client.
    * Return 0 if OK, error code if not OK
    * @return a nonzero value to indicate error.
    */
   virtual int init(int argC, char ** argV);

   /**
    * Set a pixel on the screen
    * (0,0) corresponds to the lower left of the image.
    * @param x     the X value of the pixel
    * @param y     the Y value of the pixel
    * @param color the color to set the pixel to.
    * @note: This call is not single threaded. Prepare to deal
    * with it.
    */
   virtual void set_pixel(int x, int y, const Color4 & color);

   /**
    * Shutdown the window. This call
    * will be called before the application terminates
    * (And may be an excellent place to block so the user)
    * (Can close the program)
    * @return nonzero value to indicate error
    */
   virtual int shutdown();

   /**
    * Print optional flags that this
    * image writer takes.
    * @return string of flags.
    */
   std::string flags();
private:
   int comp = 3;
   int width, height;
   std::string outName;
   std::vector<unsigned char> buffer;
};
#endif

