#include "spatial/BoundingBox.hpp"
#include "spatial/AABB_Ray.hpp"
#define VERTS_PER_BOX 8

#define aabb_min(x, y) ((x) < (y) ? (x) : (y))
#define aabb_max(x, y) ((x) > (y) ? (x) : (y))


BoundingBox::BoundingBox():
   minCoords(kMinAmount,kMinAmount,kMinAmount),
   maxCoords(kMaxAmount,kMaxAmount,kMinAmount),
   centroid(0,0,0),
   _isValid(true)
{

}
BoundingBox::BoundingBox(const Vector3 & min, const Vector3 & max):
   minCoords(min),
   maxCoords(max),
   _isValid(true)
{
   centroid = (min + max)/2;
}

BoundingBox BoundingBox::transform(Matrix4 tMat) const
{
   if(!isValid())
   {
      return BoundingBox::Invalid();
   }

   Vector3 newMin;  newMin  << kMaxAmount, kMaxAmount, kMaxAmount;
   Vector3 newMax;  newMax << kMinAmount, kMinAmount, kMinAmount;
   int iter;
   //Fast block;
   for(int i = 0; i < VERTS_PER_BOX; i++)
   {
      bool xMax = i%2;
      bool yMax = (i%4)/2;
      bool zMax = i/4;
      Vector4 newCorner; newCorner << (xMax ? maxCoords(0):minCoords(0)),
                           (yMax ? maxCoords(1):minCoords(1)),
                           (zMax ? maxCoords(2):minCoords(2)),
                           1;
      Vector3 transCorner = (tMat * newCorner).segment<3>(0);
      newMin.x() = fmin(transCorner.x(),newMin.x());
      newMin.y() = fmin(transCorner.y(),newMin.y());
      newMin.z() = fmin(transCorner.z(),newMin.z());

      newMax.x() = fmax(transCorner.x(),newMax.x());
      newMax.y() = fmax(transCorner.y(),newMax.y());
      newMax.z() = fmax(transCorner.z(),newMax.z());


   }
   return BoundingBox(newMin, newMax);
}

Amount BoundingBox::intersect(const AABB_Ray & r) const
{
   //Determine the intersection of a ray with the AABB.
   //Using the slabs method.
   //The skeleton and logic for this code is credited to
   //Owen s. for the application of the slab method, and
   //https://tavianator.com/fast-branchless-raybounding-box-intersections/, for the branchless optimization
   //by explotining the IEEE-754 floating point behavior.
   //As a note, this method has inconsistant behavior around edge cases (NAN), However,
   //the implementation is 15% more efficient than checking the edge cases (see Tavinator)
   //and usually does not lead to anything more than an additional  traverse or two in a spatial data structure

    Amount t1 = (minCoords(0) - r.origin(0))*r.recipDir(0);
    Amount t2 = (maxCoords(0) - r.origin(0))*r.recipDir(0);

    Amount tmin = aabb_min(t1, t2);
    Amount tmax = aabb_max(t1, t2);

    for (int i = 1; i < 3; ++i) {
        t1 = (minCoords(i) - r.origin(i))*r.recipDir(i);
        t2 = (maxCoords(i) - r.origin(i))*r.recipDir(i);

        tmin = aabb_max(tmin, aabb_min(t1, t2));
        tmax = aabb_min(tmax, aabb_max(t1, t2));
    }
    //Tmax msut be greater than zero, and tMin.
    if(tmax > aabb_max(tmin, 0.0))
    {
         //Return lowest non-negative
         Amount t = tmin;
         if(t < 0)
         {
            t = tmax;
         }
         return t;
    }
    else
    {
      return 0;
    }

}

bool BoundingBox::isValid() const
{
   return _isValid;
}

BoundingBox BoundingBox::merge(const BoundingBox & other) const
{
   Vector3 newMin, newMax;
   //For each component
   for(int i = 0; i < 3; i++)
   {
      newMin(i) = fmin(this->minCoords(i),other.minCoords(i));
      newMax(i) = fmax(this->maxCoords(i),other.maxCoords(i));

   }
   return BoundingBox(newMin, newMax);
}

BoundingBox BoundingBox::Invalid()
{
   BoundingBox box;
   box._isValid = false;
   return box;
}