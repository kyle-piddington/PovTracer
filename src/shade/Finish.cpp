#include "shade/Finish.hpp"
Finish::Finish():
ambient(0.1),
diffuse(0.6),
specular(0.0),
roughness(0.05),
reflection(0.0),
refraction(0.0),
ior(1.0)
{

}

void Finish::setAmbient(Amount amb)
{
   this->ambient = amb;
}
void Finish::setDiffuse(Amount diffuse)
{
   this->diffuse = diffuse;
}
void Finish::setSpecular(Amount specular)
{
   this->specular = specular;
}
void Finish::setRoughness(Amount roughness)
{
   this->roughness = roughness;
}
void Finish::setReflection(Amount reflection)
{
   this->reflection = reflection;
}
void Finish::setRefraction(Amount refraction)
{
   this->refraction = refraction;
}
void Finish::setIor(Amount ior)
{
   this->ior = ior;
}

Amount Finish::getAmbient() const
{
   return ambient;
}
Amount Finish::getDiffuse() const
{
   return diffuse;
}
Amount Finish::getSpecular() const
{
   return specular;
}
Amount Finish::getRoughness() const
{
   return roughness;
}
Amount Finish::getReflection() const
{
   return reflection;
}
bool Finish::getRefraction() const
{
   return refraction > 0;
}
Amount Finish::getIor() const
{
   return ior;
}