#pragma once
#include "precision.hpp"
struct ISampleable
{
   virtual Color3 sample(Vector2 uv) const = 0;
};