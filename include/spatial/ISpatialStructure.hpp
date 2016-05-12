#pragma once
#include "SceneObject.hpp"
#include <vector>
/**
 * Interface for spaital data structures, such as
 * BVH's, Octrees, Uniform grids.
 */
class ISpatialStructure
{
public:
   /**
    * Initialize the data structure
    * @param objects a list of objects
    */
   virtual void init(const std::vector<SceneObject> & objects) = 0;
   /**
    * Trace a ray through a data
    * structure, and return the 
    * nearest intersection with a scene object.
    * @param  ray The ray to hit
    * @return     A hit object.
    */
   virtual Hit trace(const Ray & ray) const = 0;
   
};