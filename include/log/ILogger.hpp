#pragma once
#include <string>
#include <iostream>
#include "Precision.hpp"
#include "base/Ray.hpp"
#include "base/Hit.hpp"
class ILogger{
public:

   /**
    * Log the result of a pixel
    * @param px    the pixel's px
    * @param py    the pixel's py
    * @param ray   the cast ray
    * @param t     the hit t
    * @param color the color of the pixel, 0 to 255
    */
   virtual void logPixel(int px, int py, const Ray & ray, Amount t, Color3 color) = 0;

   /**
    * Log a ray
    * @param type The type of ray
    * @param ray  The ray
    * @param amb  ambient shade component
    * @param diff diffuse shade component
    * @param spec specular shade component
    */
   virtual void logRay(const Ray & ray, Hit & hit, Color3 amb, Color3 diff, Color3 spec) = 0;

   /**
    * Print the log result.
    */
   virtual void printLog(std::ostream & str) = 0;
};