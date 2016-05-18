#include "geometry/Box.hpp"

Box::Box():
   minCoords(Vector3(0,0,0)),
   maxCoords(Vector3(0,0,0))
{

}
Box::Box(Vector3 minCoords, Vector3 maxCoords):
   minCoords(minCoords),
   maxCoords(maxCoords)
{

}
void Box::setMinCoords(Vector3 minCoords)
{
   this->minCoords = minCoords;
}
void Box::setMaxCoords(Vector3 maxCoords)
{
   this->maxCoords = maxCoords;
}

Hit Box::intersect(const Ray & ray, Amount closestT)
{
   //Determine the intersection of a ray with the AABB.
   //Using the slabs method.
   //This method ignores the branching optimizations found in BoundingBox.


   Box::Plane minPlane = Box::Plane::X_NEAR;
   Box::Plane maxPlane  = Box::Plane::X_FAR;
   Amount tmin = -INT_MAX;
   Amount tmax = INT_MAX;

   for (int i = 0; i < 3; ++i) {

      if(fabs(ray.direction(i)) > 0)
      {
         Amount t1 = (minCoords(i) - ray.origin(i))/ray.direction(i);
         Amount t2 = (maxCoords(i) - ray.origin(i))/ray.direction(i);
         bool swp = false;
         if(t1 > t2)
         {
            Amount tmp = t2;
            t2 = t1;
            t1 = tmp;
            swp = true;
         }
         if(t1 > tmin)
         {
            minPlane = (Box::Plane)(2*i + swp);
         }
         if(t2 < tmax)
         {
            maxPlane = (Box::Plane)(2*i + 1 - swp);
         }
         tmin = fmax(tmin, t1);
         tmax = fmin(tmax, t2);

      }
      else if(ray.origin(i) < minCoords(i) || ray.origin(i) > maxCoords(i))
      {
         return Hit(ray);
      }
   }
    //Tmax must be greater than zero, and tMin.
   if(tmax > fmax(tmin, 0.0))
   {
         //Return lowest non-negative
      Box::Plane intersectPlane = minPlane;
      Amount t = tmin;
      if(t < 0)
      {
         //Internal intersection
         intersectPlane = maxPlane;
         t = tmax;
      }
      //Create normal by determining which plane the point is on
      Vector3 nor = normalFor(intersectPlane);
      return Hit(ray,this,nor,t);
   }
   else
   {
      return Hit(ray);
   }
}


BoundingBox Box::createUntransformedBoundingBox() const
{
   return BoundingBox(minCoords,maxCoords);
}
Vector3 Box::normalFor(Box::Plane plane)
{
   switch(plane){
      case X_NEAR:
         return Vector3(-1,0,0);
      case X_FAR:
         return Vector3(1,0,0);
      case Y_NEAR:
         return Vector3(0,-1,0);
      case Y_FAR:
         return Vector3(0,1,0);
      case Z_NEAR:
         return Vector3(0,0,-1);
      case Z_FAR:
         return Vector3(0,0,1);
   }
}