#pragma once
#include "spatial/ISpatialStructure.hpp"
/**
 * The List Spatial structure is a baseline
 * implementation of a spatial data structure. It actually
 * does nothing, and will trace through a set of objects looking
 * for an intersection. This is as close to a baseline as possible
 */
class ListSpatialStructure : public ISpatialStructure
{
public:
   void init(const std::vector<SceneObject> & objects) override;
   Hit trace(const Ray & ray) const override;
private:
   std::vector<SceneObject> objects;
};