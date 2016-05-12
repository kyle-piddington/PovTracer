#pragma once
#include "BoundingBox.hpp"
#include "geometry/IGeometry.hpp"
/**
 * A scene object is simply a bounding box plus a geometry pointer.
 */
struct SceneObject
{
   SceneObject(std::shared_ptr<IGeometry> geometry);
   std::shared_ptr<IGeometry> geometry;
   BoundingBox bounds;
};