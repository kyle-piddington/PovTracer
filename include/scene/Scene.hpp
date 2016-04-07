#ifndef __SCENE_H__
#define __SCENE_H__
#include "camera/Camera.hpp"
#include "geometry/IGeometry.hpp"
#include "geometry/Sphere.hpp"
#include <vector>
/**
 * The Scene represents all active geometry, camera,
 * and other information that will end up
 * here eventually!
 */
class Scene
{

public:
   /**
    * Set the camera for the scene
    * @param cam the camera to view the scene from.
    */
   void setCamera(const Camera & cam);
   /**
    * Get the camera in the scene
    * @return the current camera.
    */
   const Camera & getCamera();
   /**
    * Return a hit object of the closest intersection
    *  Along a ray
    * @param  ray the ray to trace
    * @return     a hit object
    */
   Hit trace(const Ray & ray);
   /**
    * Add a sphere to the scene, and return
    * a pointer to the newly added sphere.
    */
   std::shared_ptr<Sphere> addSphere();





private:
   Camera camera;
   std::vector<std::shared_ptr<IGeometry>> geometry;
};
#endif