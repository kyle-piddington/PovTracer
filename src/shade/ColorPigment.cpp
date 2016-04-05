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