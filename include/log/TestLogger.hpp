#pragma once
#include "ILogger.hpp"
#include <vector>
/**
 * TestLogger provides a logger formatted
 * to pass Z-Wood's unit tests
 */
class TestLogger : public ILogger
{
private:
   struct rayRes
   {
      rayRes(const Hit & hit);
      std::string type;
      Ray ray;
      Ray transformed;
      Hit hit;
      Color3 amb;
      Color3 diff;
      Color3 spec;
   };

   struct traceRes
   {
      int px,py;
      Ray ray;
      Amount t;
      Color3 finalColor;
      std::vector<rayRes> traceRays;
   };
   std::vector<traceRes> traces;
   std::vector<rayRes> cRays;

public:
   virtual void logPixel(int px, int py, const Ray & ray, Amount t, Color3 color);
   virtual void logRay(Hit & hit, Color3 amb, Color3 diff, Color3 spec);
   virtual void printLog(std::ostream & str);




};