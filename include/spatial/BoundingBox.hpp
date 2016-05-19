#pragma once

#include "Precision.hpp"
#include "base/Ray.hpp"
#include "spatial/AABB_Ray.hpp"
/**
 * A Bounding Box is a small struct containing the minimum
 * and maximum coordinates of some object.
 */
struct BoundingBox
{

   BoundingBox();
   BoundingBox(const Vector3 & minCoords, const Vector3 & maxCoords);
   /**
    * Create a new bounding box by transforming
    * the old one, and analyzing the new boundaris
    * @param  mat the transformation matrix
    * @return     a new bounding box.
    */
   BoundingBox transform(Matrix4 mat) const;

   BoundingBox merge(const BoundingBox & other) const;
   /**
    * Determine if a ray intersects with this bounding box.
    * @param  ray The intersecting rays
    * @return     nonzero  if the ray intersects.
    */
   Amount intersect(const AABB_Ray & ray) const;

   /**
    * Determine if a box intersects another box
    * @param  other the other box
    * @return       true if it intersects.
    */
   bool intersects(const BoundingBox & other) const;

   /**
    * Planes return invalid bounding boxes. If the mincoord and
    * maxCoord of a bounding box are identical, it is
    * considered invalid.
    * @return true if it is valid.
    */
   bool isValid() const;

   Amount volume();



   /**
    * Create an invalid bounding boxe
    * @return an invalid box.
    */
   static BoundingBox Invalid();


   Vector3 centroid;
   Vector3 minCoords;
   Vector3 maxCoords;
private:
   bool _isValid;
};
