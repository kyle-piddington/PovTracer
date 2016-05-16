#include "spatial/ListSpatialStructure.hpp"

ListSpatialStructure::init(const std::vector<SceneObject> & objects)
{
   this->objects = objects;
}

Hit trace(const Ray & ray)
{
   Amount mDist = -1;
   Hit returnHit(ray);
   for (std::vector<std::shared_ptr<SceneObject>>::iterator i = objects.begin(); i != objects.end(); ++i)
   {
      Hit hit = (i)->geometry->intersectTransform(ray, mDist);
      if(hit.didHit() && (mDist < 0 || hit.getDistance() < mDist))
      {
         returnHit = hit;
         mDist = returnHit.getDistance();
      }
   }
   return returnHit;
}