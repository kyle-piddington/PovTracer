#include "geometry/IGeometry.hpp"
#include "shade/ColorPigment.hpp"
#include "math/Maths.hpp"
#include "shade/NullMapping.hpp"

IGeometry::IGeometry():
   pigment(ColorPigment::CreateDefault()),
   mapping(std::make_shared<NullMapping>()),
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
      Ray transformed = transformRay(ray);
      Hit tIntersect = intersect(transformed, closestT);
      //Modify tIntersect if hit to transform back
      //to world coordinates (Short circuit if it's not worth it)
      if(tIntersect.didHit())
      {

         //Create normal
         Vector3 nor = (transformInv.transpose() * Maths::make_vec4(tIntersect.getNormal(),0)).segment<3>(0);
         return Hit(ray,this,nor,tIntersect.getT());
      }
      else
      {
         return Hit(ray);
      }
   }
}

Ray IGeometry::transformRay(const Ray & ray) const
{
   Ray transformed(ray);
   transformed.origin = (transformInv * Maths::make_vec4(transformed.origin,1)).segment<3>(0);
   transformed.direction = (transformInv * Maths::make_vec4(transformed.direction,0)).segment<3>(0);
   return transformed;
}

void IGeometry::setPigment(std::shared_ptr<IPigment> pigment)
{
   this->pigment = pigment;
}

void IGeometry::setTransform(const Matrix4 & transform)
{
   if(Matrix4::Identity() != transform)
   {
      //Inverse the transform matrix for hit detection
      this->transformInv = transform.inverse();
      transformed = true;
   }

}

BoundingBox IGeometry::createBoundingBox()
{
   BoundingBox bBox = this->createUntransformedBoundingBox();
   if(bBox.isValid() && transformed)
   {
      bBox = bBox.transform(getTransform());
   }
   this->box = bBox;
   boxInitted = true;
   return bBox;
}

BoundingBox IGeometry::getBoundingBox() const
{
   assert(boxInitted);
   return box;
}
Matrix4 IGeometry::getTransform() const
{
   return transformInv.inverse();
}

std::shared_ptr<IPigment>  IGeometry::getPigment()
{
   return pigment;

}
std::shared_ptr<IPigment> * IGeometry::getPigmentPtr()
{
   return &pigment;
}
std::shared_ptr<IMapping> IGeometry::getMapping()
{
   return mapping;
}

std::shared_ptr<IMapping> * IGeometry::getMappingPtr()
{
   return &mapping;
}
Finish * IGeometry::getFinish()
{
   return &finish;
}

