#include "spatial/Octree.hpp"

Octree::Octree(int maxDepth):
   maxDepth(maxDepth)
{

}

Amount calculateMaxBounds(const std::vector<SceneObject> & objects)
{
   Amount maxBound = -INT_MAX;
   //Largest power of 2 that contains all objects
   //
   for (auto i = objects.begin(); i != objects.end(); ++i)
   {
      for(int dim = 0; dim < 3; dim++)
      {
         maxBound = fmax(maxBound,fmax(fabs(i->bounds.maxCoords(dim)),fabs(i->bounds.minCoords(dim))));
      }
   }
   //Octree bounds with largest power of two.

   Amount maxLog2Bounds = pow(2, ceil(log2(maxBound)));
   return maxLog2Bounds/2;
}

void Octree::splitTree(std::vector<Node> & children, const std::vector<SceneObject *>  & objects, Vector3 minBounds, Vector3 maxBounds, int depth)
{
   children.resize(8);
   //Create the new children
   for(int i = 0; i < 8; i++)
   {
      bool zBox = i%2;
      bool yBox = (i%4)/2;
      bool xBox = i/4;
      Vector3 offset = Vector3(xBox, yBox, zBox).cwiseProduct((maxBounds-minBounds))/2;
      BoundingBox containingBox(minBounds + offset, minBounds + offset + (maxBounds-minBounds)/2);
      std::vector<SceneObject *> childObjects;
      for (auto obj = objects.begin(); obj != objects.end(); ++obj)
      {
         if(containingBox.intersects((*obj)->bounds))
         {
            childObjects.push_back(*obj);
         }
      }
      build(children[i],childObjects,minBounds + offset, minBounds + offset + (maxBounds - minBounds)/2, depth+1);
   }
}

void Octree::build(Node & node, const std::vector<SceneObject *> & objects, Vector3 minBounds, Vector3 maxBounds, int depth)
{

   if(depth >= maxDepth || objects.size() <= 1)
   {
      node.terminal = true;
      for (int i = 0; i < objects.size(); ++i)
      {
         node.objects.push_back(objects[i]);
      }
   }
   else //split
   {
      splitTree(node.children,objects,minBounds,maxBounds, depth);
   }
}

Hit Octree::trace(const Ray & ray) const
{
   return Hit(ray);
}

Hit Octree::Node::trace(const Ray & ray)
{
   return Hit(ray);
}
void Octree::init(const std::vector<SceneObject> & objects)
{
   //Copy the objects into the spatial structure
   this->objects = std::vector<SceneObject>(objects);
   std::vector<SceneObject *> objectPointers;
   for(int i = 0; i < this->objects.size(); i++)
   {
      objectPointers.push_back(&this->objects[i]);
   }
   Amount mBound = calculateMaxBounds(objects);
   bounds = BoundingBox(Vector3(-mBound,-mBound,-mBound), Vector3(mBound,mBound,mBound));
   //Create octree
   build(root, objectPointers,bounds.minCoords, bounds.maxCoords,0);
}