#include "log/TestLogger.hpp"

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

void TestLogger::logRay(const Ray & ray, Hit & hit, Color3 amb, Color3 diff, Color3 spec)
{
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
   }
   result.ray = ray;
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
         str << " T: " << i->t << " Color: " << i->finalColor.transpose();
      }
      else
      {
         str << "No Intersection";
      }
      str << std::endl << "----" << std::endl;
      for (std::vector<rayRes>::iterator ray = i->traceRays.begin(); ray != i->traceRays.end(); ++ray)
      {
         str << "Iteration Type:" << ray->type << std::endl;
         str << "Ray: " << ray->ray << std::endl;
         if(ray->hit.didHit())
         {
            str << "Hit Object ID (" << ray->hit.ID() << ")"
                <<" at T=" << ray->hit.getT()
                << ", Intersection = " << ray->hit.getHitpoint().transpose() << std::endl;
            str << "Ambient: " << ray->amb.transpose() << std::endl;
            str << "Diffuse: " << ray->diff.transpose() << std::endl;
            str << "Specular: "<< ray->spec.transpose() << std::endl;

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