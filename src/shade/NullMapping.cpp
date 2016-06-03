#include "shade/NullMapping.hpp"
Vector2 NullMapping::getUV(const Hit & hit) const
{
   return Vector2::Zero();
}