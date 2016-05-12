#include "spatial/ListSpatialStructure.hpp"

void ListSpatialStructure::init(const std::vector<SceneObject> & objects)
{
   this->objects = objects;
}

Hit ListSpatialStructure::trace(const Ray & ray) const
{
   Amount mDist = -1;
   Hit returnHit(ray);
   for (auto i = objects.begin(); i != objects.end(); ++i)
   {
      Hit hit = i->geometry->intersectTransform(ray, mDist);
      if(hit.didHit() && (mDist < 0 || hit.getDistance() < mDist))
      {
         returnHit = hit;
         mDist = returnHit.getDistance();
      }
   }
   return returnHit;
}