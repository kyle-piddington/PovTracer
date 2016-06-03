#pragma once
#include "shade/IMapping.hpp"
struct NullMapping : public IMapping
{
   Vector2 getUV(const Hit & hit) const override;
};