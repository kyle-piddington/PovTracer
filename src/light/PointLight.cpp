#include "light/PointLight.hpp"

PointLight::PointLight():
   position(Vector3(0,0,0)),
   color(Color4(0,0,0,0))
{

}

PointLight::PointLight(Vector3 position, Vector3 color):
   position(position),
   color(color.x(),color.y(),color.z(),1.0)
{

}

void PointLight::setPosition(const Vector3 & position)
{
   this->position = position;
}

void PointLight::setColor(const Vector3 & color)
{
   this->color = Color4(color.x(),color.y(),color.z(),1.0);
}

Vector3 PointLight::getPosition() const
{
   return position;
}

Color4 PointLight::getColor() const
{
   return color;
}