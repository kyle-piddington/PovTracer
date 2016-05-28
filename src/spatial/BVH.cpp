#include "spatial/BVH.hpp"

void BVH::init(const std::vector<SceneObject> & objects)
{
   root = createBVHNode(objects,0);
}


bool CompareXAxis(const SceneObject & left, const SceneObject & right)
{
   return left.bounds.centroid.x() < right.bounds.centroid.x();
}
bool CompareYAxis(const SceneObject & left, const SceneObject & right)
{
   return left.bounds.centroid.y() < right.bounds.centroid.y();
}
bool CompareZAxis(const SceneObject & left, const SceneObject & right)
{
   return left.bounds.centroid.z() < right.bounds.centroid.z();
}


void BVH::SortObjects(std::vector<SceneObject> * objects, SplitAxis axis)
{
   switch(axis)
   {
      case X_AXIS:
         std::sort(objects->begin(), objects->end(), CompareXAxis);
         break;
      case Y_AXIS:
         std::sort(objects->begin(), objects->end(), CompareYAxis);
         break;
      case Z_AXIS:
         std::sort(objects->begin(), objects->end(), CompareZAxis);
         break;
   }
}

BVH::SplitAxis BVH::GetNextAxis(SplitAxis cAxis)
{
   switch(cAxis)
   {
      case X_AXIS:
         return Y_AXIS;
      case Y_AXIS:
         return Z_AXIS;
      case Z_AXIS:
         return X_AXIS;
   }
}


BVH::SplitAxis BVH::GetLongestAxis(const std::vector<SceneObject> & objects)
{
   Vector3 minCoords, maxCoords;
   if(objects.size() > 1)
   {
      minCoords = objects[0].bounds.minCoords;
      maxCoords = objects[0].bounds.maxCoords;
      for(int i = 1; i < objects.size(); i++)
      {
         minCoords = minCoords.cwiseMin(objects[i].bounds.minCoords);
         maxCoords = maxCoords.cwiseMax(objects[i].bounds.maxCoords);
      }
      Vector3 diff = maxCoords - minCoords;

      BVH::SplitAxis retAxis = diff(0) > diff(1)? BVH::SplitAxis::X_AXIS : BVH::SplitAxis::Y_AXIS;
      retAxis = diff((int)retAxis) > diff(2) ? retAxis : BVH::SplitAxis::Z_AXIS;
      return retAxis;

   }
   return BVH::SplitAxis::X_AXIS;
}

std::shared_ptr<BVH::IBVHNode> BVH::createBVHNode(std::vector<SceneObject> objects, int depth)
{
   if(objects.size() == 0)
   {
      return nullptr;
   }
   else if(objects.size() == 1)
   {
      return std::make_shared<BVH::BVHLeaf>(objects[0]);
   }
   else
   {
   
      //Sort and split recursivley, swapping the split axis each time.
      SplitAxis axis = GetLongestAxis(objects);
      
      SortObjects(&objects,axis);
      //SplitAxis nextAxis = GetNextAxis(axis);
      std::shared_ptr<BVH::BVHNode> newNode = std::make_shared<BVH::BVHNode>();
      newNode->depth = depth;
      newNode->left = createBVHNode(
                        std::vector<SceneObject>(objects.begin(), objects.begin() + objects.size()/2), depth+1
                        );
      newNode->right = createBVHNode(
                        std::vector<SceneObject>(objects.begin() + objects.size()/2, objects.end()), depth+1
                           );

      //Create bounding box
      newNode->nodeBounds = newNode->left->getBox().merge(newNode->right->getBox());
      return newNode;
   }
}



Hit BVH::trace(const Ray & ray) const 
{
   if(root != nullptr)
   {
      return root->trace(AABB_Ray(ray), ray, -1);
   }
   else
   {
      return Hit(ray);
   }
}




BVH::BVHNode::BVHNode():
   left(nullptr),
   right(nullptr)
{

}


const BoundingBox & BVH::BVHNode::getBox() const
{
   return nodeBounds;
}

Hit BVH::BVHNode::trace(const AABB_Ray & aabb_ray, const Ray & ray, Amount minT)
{
   Hit retHit(ray);
   //First check to see if this hit intersects with this node.
   Amount thisT = getBox().intersect(aabb_ray);

   if(thisT > 0 && (thisT < minT || minT < 0))
   {
      if(this->left != nullptr)
      {
         Hit hLeft = this->left->trace(aabb_ray,ray,minT);
         if(hLeft.didHit() && (hLeft.getT() < minT || minT < 0))
         {
            retHit = hLeft;
            minT = hLeft.getT();
         }
      }
      if(this->right != nullptr)
      {
         Hit hRight = this->right->trace(aabb_ray,ray,minT);
         if(hRight.didHit() && (hRight.getT() < minT || minT < 0))
         {
            retHit = hRight;
         }
      }
   }


   return retHit;
}


BVH::BVHLeaf::BVHLeaf(SceneObject object):
   object(object)
{

}

Hit BVH::BVHLeaf::trace(const AABB_Ray & aabb_ray, const Ray & ray, Amount minT)
{
   if(object.bounds.intersect(aabb_ray)){
      return object.geometry->intersectTransform(ray,minT);
   }
   return Hit(ray);
}
const BoundingBox & BVH::BVHLeaf::getBox() const
{
   return object.bounds;
}
