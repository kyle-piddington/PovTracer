#include "spatial/SceneObject.hpp"

SceneObject::SceneObject(std::shared_ptr<IGeometry> geometry):
   geometry(geometry)
{
   this->bounds = geometry->createBoundingBox();
}