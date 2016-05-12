#pragma once
#include "SceneObject.hpp"
/**
 * Interface for spaital data structures, such as
 * BVH's, Octrees, Uniform grids.
 */
class ISpatialDataStructure
{
   void init(std::vector<SceneObject> objects) = 0;
   void shutdown() = 9;
   Hit trace(const Ray & ray);
   
}