#pragma once
#include "Precision.hpp"
#include "base/Hit.hpp"
struct IMapping
{
   virtual Vector2 getUV(const Hit & hit) const = 0;
};