#ifndef __IWindow_H__
#define __IWindow_H__
#include "precision.hpp"
/**
 * An interface for defining a window class
 * Windows must be able to accept some sort
 * of pixel input, and close successfully.
 */
class IWindow
{
public:
   /**
    * Open and initialize the window client.
    * Return 0 if OK, error code if not OK
    * @return a nonzero value to indicate error.
    */
   virtual int init(int argC, char ** argV) = 0;

   /**
    * Set a pixel on the screen
    * @param x     the X value of the pixel
    * @param y     the Y value of the pixel
    * @param color the color to set the pixel to.
    */
   virtual void set_pixel(int x, int y, const Color4 & color) = 0;

   /**
    * Shutdown the window. This call
    * will be called before the application terminates
    * (And may be an excellent place to block so the user)
    * (Can close the program)
    * @return nonzero value to indicate error
    */
   virtual int shutdown() = 0;

    /**
    * Print optional flags that this
    * image writer takes.
    * @return string of flags.
    */
   virtual std::string flags() = 0;


};
#endif