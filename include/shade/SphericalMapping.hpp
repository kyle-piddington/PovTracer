#pragma once
#include "shade/IMapping.hpp"
class SphericalMapping : public IMapping
{
   Vector2 getUV(const Hit & hit) const override;
};