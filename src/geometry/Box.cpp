#include "Box.hpp"

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
void Box::setMaxCoords(vector3 maxCoords)
{
   this->maxCoords = maxCoords;
}

Hit Box::intersect(const Ray & ray, Amount closestT)
{
   
}