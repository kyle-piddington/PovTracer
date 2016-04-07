#include "shade/ColorPigment.hpp"

ColorPigment::ColorPigment(const Color4 & color):
   thisColor(color)
{

}
ColorPigment::ColorPigment(const Color3 & color):
   thisColor(Color4(color.x(),color.y(),color.z(),0.0))
{

}
Color4 ColorPigment::getColor(const Hit & hit) const
{
   return thisColor;
}

std::shared_ptr<IPigment> ColorPigment::CreateDefault()
{
   return std::shared_ptr<IPigment>(new ColorPigment(Color3(1,0,0)));
}
std::shared_ptr<IPigment> ColorPigment::Create(const Color3 & color)
{
   return std::shared_ptr<IPigment>(new ColorPigment(color));
}