#include "scene/Scene.hpp"
#include "spatial/ListSpatialStructure.hpp"
Scene::Scene():
   backgroundColor(0,0,0,0),
   sStructureInitted(false)
{
   spatialStructure = std::make_shared<ListSpatialStructure>();
}
void Scene::setCamera(const Camera & cam)
{
   this->camera = cam;
}

const Camera & Scene::getCamera()
{
   return this->camera;
}


void Scene::initialize()
{
   std::vector<SceneObject> objs;
   for (std::vector<std::shared_ptr<IGeometry>>::iterator i = geometry.begin(); i != geometry.end(); ++i)
   {
      objs.push_back(*i);
   }
   spatialStructure->init(objs);
}
std::shared_ptr<Sphere> Scene::addSphere()
{
   auto sphPt = std::make_shared<Sphere>();
   geometry.push_back(std::static_pointer_cast<IGeometry>(sphPt));
   return sphPt;
}

std::shared_ptr<Plane> Scene::addPlane()
{
   auto planePt = std::make_shared<Plane>();
   planeGeometry.push_back(std::static_pointer_cast<IGeometry>(planePt));
   return planePt;
}

std::shared_ptr<Triangle> Scene::addTriangle(Vector3 vA, Vector3 vB, Vector3 vC)
{
   auto triPt = std::make_shared<Triangle>(vA, vB, vC);
   geometry.push_back(std::static_pointer_cast<IGeometry>(triPt));
   return triPt;
}

std::shared_ptr<Box> Scene::addBox()
{
   auto boxPt = std::make_shared<Box>();
   geometry.push_back(std::static_pointer_cast<IGeometry>(boxPt));
   return boxPt;
}
PointLight & Scene::addPointLight()
{
   lights.push_back(PointLight());
   return lights.back();
}

Hit Scene::trace(const Ray & ray)
{
   //NOTE: NOT THREADSAFE!
   if(!sStructureInitted)
   {
      //Lock
      //Double guard for mutex
      #pragma omp critical
      if(!sStructureInitted)
      {
         initialize();
         sStructureInitted = true;
      }
      //Unlock
   }
   //Get hit
   Hit returnHit = spatialStructure->trace(ray);
   Amount mDist = returnHit.getDistance();
   //Planes can't be included in spatial structures,
   //trace through the rest of them to find any interesections
   for (std::vector<std::shared_ptr<IGeometry>>::iterator i = planeGeometry.begin(); i != planeGeometry.end(); ++i)
   {
      Hit hit = (*i)->intersectTransform(ray, mDist);
      if(hit.didHit() && (mDist < 0 || hit.getDistance() < mDist))
      {
         returnHit = hit;
         mDist = returnHit.getDistance();
      }
   }
   returnHit.setScene(this);
   return returnHit;
}

const std::vector<PointLight> & Scene::getLights()
{
   return lights;
}

Color4 Scene::getBackgroundColor() const
{
   return backgroundColor;
}

void Scene::provideSpatialStructure(std::shared_ptr<ISpatialStructure> structure)
{
   this->spatialStructure = structure;
}