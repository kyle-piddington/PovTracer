#ifndef __SCENE_H__
#define __SCENE_H__
#include "camera/Camera.hpp"
#include "geometry/IGeometry.hpp"
#include "geometry/Sphere.hpp"
#include "geometry/Triangle.hpp"
#include "light/PointLight.hpp"
#include "geometry/Plane.hpp"
#include "spatial/ISpatialStructure.hpp"

#include <vector>
/**
 * The Scene represents all active geometry, camera,
 * and other information that will end up
 * here eventually!
 */
class Scene
{

public:

   Scene();

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

   /**
    * Add a plane to the scene, and return
    * a pointer to the newly added plane
    */
   std::shared_ptr<Plane> addPlane();

   /** Add a triangle to the scene, and return
   a poitner to the new triangle.
   The signiture here differs from the other signitures
   due to the triangle having to create it's normal. */
   std::shared_ptr<Triangle> addTriangle(Vector3 vA, Vector3 vB, Vector3 vC);

   /**
    * Add a light to the scene, and retunr a reference
    * to the newly added light.
    * @return [description]
    */
   PointLight & addPointLight();

   /**
    * Set up any BVH/Spatial data structures
    * that need to be set up.
    */
   virtual void initialize();

   /**
    * Provide a new spatial data structure
    * for the scene to use during tracing.
    * @param structure a new structure
    */
   void provideSpatialStructure(std::shared_ptr<ISpatialStructure> structure);

   /**
    * Retrieve all the lights in the scene
    */
   const std::vector<PointLight> & getLights();


   Color4 getBackgroundColor() const;



private:
   bool sStructureInitted;
   Color4 backgroundColor;
   Camera camera;
   std::vector<std::shared_ptr<IGeometry>> geometry;

   //Planes don't have a traditional boudning box,
   //and are removed from the spatial data structure.
   std::vector<std::shared_ptr<IGeometry>> planeGeometry;

   std::vector<PointLight> lights;
   std::shared_ptr<ISpatialStructure> spatialStructure;

};
#endif