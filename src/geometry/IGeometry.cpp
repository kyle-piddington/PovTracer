#include "geometry/IGeometry.hpp"
#include "shade/ColorPigment.hpp"
#include "math/Maths.hpp"


IGeometry::IGeometry():
   pigment(ColorPigment::CreateDefault()),
   transform(Matrix4::Identity()),
   transformInv(Matrix4::Identity())
   {

   }

Hit IGeometry::intersectTransform(const Ray & ray, Amount closestT)
{
   //Transform first
   if(!transformed)
   {
      return intersect(ray, closestT);
   }
   else
   {
      Ray transformed(ray);
      transformed.origin = (transformInv * Maths::make_vec4(transformed.origin,1)).segment<3>(0);
      transformed.direction = (transformInv * Maths::make_vec4(transformed.direction,0)).segment<3>(0);
      Hit tIntersect = intersect(transformed, closestT);
      //Modify tIntersect if hit to transform back
      //to world coordinates (Short circuit if it's not worth it)
      if(tIntersect.didHit())
      {
         //Create normal
         Vector3 nor = (transformInv.transpose() * Maths::make_vec4(tIntersect.getNormal(),1)).segment<3>(0);
         return Hit(ray,this,nor,tIntersect.getT());
      }
      else
      {
         return Hit(ray);
      }
      //Intersect with geometry after transform.
      
   }
}

void IGeometry::setPigment(std::shared_ptr<IPigment> pigment)
{
   this->pigment = pigment;
}

void IGeometry::setTransform(const Matrix4 & transform)
{
   std::cout << "Transform is now :" << transform << std::endl;
   this->transform = transform;
   //Inverse the transform matrix for hit detection
   this->transformInv = transform.inverse();
   std::cout << "Inverse is now :" << transformInv << std::endl;
   transformed = true;
}
std::shared_ptr<IPigment>  IGeometry::getPigment()
{
   return pigment;

}

std::shared_ptr<IPigment> * IGeometry::getPigmentPtr()
{
   return &pigment;
}
Finish * IGeometry::getFinish()
{
   return &finish;
}

