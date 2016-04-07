#include "scene/Scene.hpp"
void Scene::setCamera(const Camera & cam)
{
   this->camera = cam;
}

const Camera & Scene::getCamera()
{
   return this->camera;
}

std::shared_ptr<Sphere> Scene::addSphere()
{
   auto sphPt = std::make_shared<Sphere>();
   geometry.push_back(std::static_pointer_cast<IGeometry>(sphPt));
   return sphPt;
}

Hit Scene::trace(const Ray & ray)
{
   Amount mDist = -1;
   Hit returnHit(ray);
   for (std::vector<std::shared_ptr<IGeometry>>::iterator i = geometry.begin(); i != geometry.end(); ++i)
   {
      Hit hit = (*i)->intersect(ray);
      if(hit.didHit() && (mDist < 0 || hit.getDistance() < mDist))
      {
         returnHit = hit;
         mDist = returnHit.getDistance();
      }
   }
   return returnHit;
}