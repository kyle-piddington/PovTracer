#pragma once
#include "ILogger.hpp"
/**
 * NullLogger provides no logging information, and is supplied to a renderer by default.
 */
class NullLogger : public ILogger
{
   /**
    * Log the result of a pixel
    * @param px    the pixel's px
    * @param py    the pixel's py
    * @param ray   the cast ray
    * @param t     the hit t
    * @param color the color of the pixel, 0 to 255
    */
   virtual void logPixel(int px, int py, const Ray & ray, Amount t, Color3 color){}

   /**
    * Log a ray
    * @param type The type of ray
    * @param ray  The ray
    * @param amb  ambient shade component
    * @param diff diffuse shade component
    * @param spec specular shade component
    */
   virtual void logRay(Hit & hit, Color3 amb, Color3 diff, Color3 spec){}

   /**
    * Print the log result.
    */
   virtual void printLog(std::ostream & str){}
};