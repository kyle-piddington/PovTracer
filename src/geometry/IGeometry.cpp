#include "geometry/IGeometry.hpp"
#include "shade/ColorPigment.hpp"


IGeometry::IGeometry():
   pigment(ColorPigment::CreateDefault())
   {

   }

void IGeometry::setPigment(std::shared_ptr<IPigment> pigment)
{
   this->pigment = pigment;
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