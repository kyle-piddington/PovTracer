#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include "Precision.hpp"
#include "base/Hit.hpp"
#include "base/Ray.hpp"
#include "shade/IPigment.hpp"
#include "shade/Finish.hpp"
#include "spatial/BoundingBox.hpp"
#include "shade/IMapping.hpp"
/**
 * The IGeometry interface is used by the Raytracer
 * to intersect rays with objects
 */
class IGeometry
{
public:
    IGeometry();

   Hit intersectTransform(const Ray & ray, Amount closestT);
   virtual Hit intersect(const Ray & ray, Amount closestT) = 0;

   Ray transformRay(const Ray & ray) const;

   /**
    * Create an axis-aligned bounding box of
    * a transformed geometric object.
    * @return the object's bounding box;
    */
   virtual BoundingBox createBoundingBox() ;


   virtual BoundingBox getBoundingBox() const;

   void setPigment(std::shared_ptr<IPigment> pigment);
   void setTransform(const Matrix4 & transform);
   /**
    * Get a reference to the pigment.
    */
   std::shared_ptr<IPigment>  getPigment();

   std::shared_ptr<IMapping>  getMapping();
   /**
    * Get a reference to the pigment pointer
    */
   std::shared_ptr<IPigment> * getPigmentPtr();

   std::shared_ptr<IMapping> * getMappingPtr();

   Finish * getFinish();

   /**
    * Return the transformation matrix
    * @note: minimize calls to this function, as it executes a matrix inverse
    * operation every call. Ideally, this is called exactly once per object to build a bounding
    * box.
    * @return a matrix mapping local space to world space.
    */
   Matrix4 getTransform() const;

   Vector3 getLocalPoint(const Vector3 & wPt) const;

   virtual std::string getName() const = 0;

protected:
  virtual BoundingBox createUntransformedBoundingBox() const = 0;

private:
   BoundingBox box;
   bool boxInitted;
   bool transformed;
   Matrix4 transformInv;
   std::shared_ptr<IPigment> pigment;
   std::shared_ptr<IMapping> mapping;
   Finish finish;
};
#endif