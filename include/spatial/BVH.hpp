#pragma once

#include "ISpatialStructure.hpp"
#include "BoundingBox.hpp"
/**
 * The BVH Spatial structure creates a
 * bounding volume heiarchy around
 * a set of geometry, and provides
 * more efficient tracing through a scene.
 */
class BVH : public ISpatialStructure
{
public:
   void init(const std::vector<SceneObject> & objects) override;
   Hit trace(const Ray & ray) const override;
private:

   //Private enum for iterating through xyz axis
   enum SplitAxis
   {
      X_AXIS,
      Y_AXIS,
      Z_AXIS
   };
   static SplitAxis GetNextAxis(SplitAxis cAxis);
   static SplitAxis GetLongestAxis(const std::vector<SceneObject> & objects);
   
   /**
    * Interface for tree node.
    */
   struct IBVHNode
   {
      virtual Hit trace(const AABB_Ray & aabb, const Ray & ray, Amount minT) = 0;
      virtual const BoundingBox & getBox() const = 0;

   };
   /**
    * Split node in tree,
    * contains max 2 children
    */
   struct BVHNode : public IBVHNode
   {
      BVHNode();
      std::shared_ptr<IBVHNode> left;
      std::shared_ptr<IBVHNode> right;
      virtual Hit trace(const AABB_Ray & aabb, const Ray & ray, Amount minT);
      virtual const BoundingBox & getBox() const;
      BoundingBox nodeBounds;
   };

   /**
    * Leaf node in tree
    * No children.
    */
   struct BVHLeaf : public IBVHNode
   {
      BVHLeaf(SceneObject object);
      SceneObject object;
      virtual Hit trace(const AABB_Ray & aabb, const Ray & ray, Amount minT) override;
      const BoundingBox & getBox() const override;
   };

   static std::shared_ptr<IBVHNode> createBVHNode(std::vector<SceneObject> objects);
   /**
    * sort the BVH objects in a list.
    * @param  objects The objects to sort
    * @param  axis    The axis to split on
    */
   static void SortObjects(std::vector<SceneObject> * objects, SplitAxis axis);

   Hit trace(const AABB_Ray & aabb_ray, const Ray & ray, std::shared_ptr<BVHNode> root, Amount t) const;

   std::shared_ptr<IBVHNode> root;

};