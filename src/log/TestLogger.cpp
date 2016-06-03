#include "log/TestLogger.hpp"
#include "geometry/IGeometry.hpp"
TestLogger::rayRes::rayRes(const Hit & hit):
   hit(hit){}

void TestLogger::logPixel(int px, int py, const Ray & ray, Amount t, Color3 color)
{
   traceRes result;
   result.px = px;
   result.py = py;
   result.ray = ray;
   result.t = t;
   result.finalColor = color;
   result.traceRays = cRays;
   cRays.clear();
   traces.push_back(result);
}

void TestLogger::logRay(Hit & hit, Color3 amb, Color3 diff, Color3 spec)
{
   Ray ray = hit.getRay();
   rayRes result(hit);
   switch(ray.type){
      case Ray::PRIMARY:
         result.type = "Primary";
         break;
      case Ray::REFLECTION:
         result.type = "Reflection";
         break;
      case Ray::REFRACTION:
         result.type = "Refraction";
         break;
      case Ray::SHADOW:
         result.type = "Shadow";
   }
   result.ray = hit.getRay();
   if(hit.didHit())
   {
      result.transformed = hit.getGeometry()->transformRay(hit.getRay());
   }
   result.amb = amb;
   result.diff = diff;
   result.spec = spec;
   cRays.push_back(result);
}


void TestLogger::printLog(std::ostream & str)
{
   for (std::vector<traceRes>::iterator i = traces.begin(); i != traces.end(); ++i)
   {
      str << "Pixel: ["<< i->px << "," << i->py << "] Ray: " << i->ray;
      if(i->t > 0)
      {
         str << " T: " << i->t << std::endl << " Color: " << (255*i->finalColor.transpose()).cast<int>();
      }
      else
      {
         str << "No Intersection";
      }
      str << std::endl << "----" << std::endl;
      for (std::vector<rayRes>::iterator ray = i->traceRays.begin(); ray != i->traceRays.end(); ++ray)
      {
         str << "Iteration Type: " << ray->type << std::endl;
         str << "Ray: " << ray->ray << std::endl;
         if(ray->hit.didHit())
         {
            str << "Hit: " << ray->hit.getHitpoint().transpose() << " on " << ray->hit.getGeometry()->getName() << std::endl;
            str << "T: " << ray->hit.getT() << std::endl;
         }
         else
         {
            str << "No Intersection." << std::endl;
         }
         str << "----" << std::endl;
      }
      str << "==========" << std::endl;
   }
}

