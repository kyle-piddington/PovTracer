#pragma once

#include "ISpatialStructure.hpp"
#include "BoundingBox.hpp"
/**
 * The BVH Spatial structure creates a
 * bounding volume heiarchy around
 * a set of geometry, and provides
 * more efficient tracing through a scene.
 */
class Octree : public ISpatialStructure
{
public:
   Octree(int maxDepth);
   void init(const std::vector<SceneObject> & objects) override;
   Hit trace(const Ray & ray) const override;
private:

   struct Node
   {
      virtual Hit trace(const Ray & ray);
      std::vector<SceneObject *> objects;
      bool terminal;
      std::vector<Node> children;
   };

   void build(Node & node, const std::vector<SceneObject * > & objs, Vector3 minBounds, Vector3 maxBounds, int depth);
   void splitTree(std::vector<Node> & children, const std::vector<SceneObject *> & objects, Vector3 minBounds, Vector3 maxBounds, int depth);
   /**
    * Interface for tree node.
    */
   

   Hit trace(const Ray & ray, Amount t) const;

   Node root;
   BoundingBox bounds;
   std::vector<SceneObject> objects;
   int maxDepth;
};