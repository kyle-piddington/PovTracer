#include "shade/SphericalMapping.hpp"
#include "geometry/IGeometry.hpp"
Vector2 SphericalMapping::getUV(const Hit & hit) const
{
   Vector3 diff = hit.getGeometry()->getLocalPoint(hit.getHitpoint());// - hit.getGeometry()->getBoundingBox().centroid;
   Amount theta = acos(diff.y()/diff.norm());
   Amount phi   = atan2(diff.z(),diff.x());
  
   return Vector2((phi + M_PI)/(2*M_PI),(theta)/(M_PI));
}