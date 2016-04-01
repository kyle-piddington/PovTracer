#ifndef __SCENE_H__
#define __SCENE_H__
#include "camera/Camera.hpp"
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
private:
   Camera camera;
};
#endif