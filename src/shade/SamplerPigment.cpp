#include "shade/SamplerPigment.hpp"
#include "geometry/IGeometry.hpp"
SamplerPigment::SamplerPigment(std::shared_ptr<ISampleable> samplable):
   samplable(samplable)
{

}

Color4 SamplerPigment::getColor(const Hit & hit) const
{
   Vector2 uv = hit.getGeometry()->getMapping()->getUV(hit);
   Color4 retColor;
   retColor << samplable->sample(uv), 0;
   return retColor;
}