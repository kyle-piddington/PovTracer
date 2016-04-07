#include "camera/Camera.hpp"
#include "math/Maths.hpp"
#include "base/Ray.hpp"
Camera::Camera():
  location(0,0,0),
  direction(0,0,1),
  initLookAt(false),
  look_at(0,0,1),
  sky(0,1,0),
  upVec(0,1,0),
  rightVec(1.33,0,0)
  {

  }

Ray Camera::getRay(Amount u, Amount v) const
{
  Ray r;
  r.origin = this->location;
  r.direction = (rightVec * u + upVec * v + direction).normalized();
  return r;
}
void Camera::setLocation(const Vector3 & location)
{
  this->location = location;
}
void Camera::setLookAt(const Vector3 & look_at)
{
  this->look_at = look_at;
  initLookAt=true;
}
void Camera::setSky(const Vector3 & sky)
{
  this->sky = sky;
}
void Camera::setUp(const Vector3 & up)
{
  this->upVec = up;
}
void Camera::setRight(const Vector3 right)
{
  this->rightVec = right;
}
void Camera::setDirection(const Vector3 & direction)
{
  this->direction = direction;
}
void Camera::setAngle(const double angle)
{
  double dirLen = 0.5 * rightVec.norm() / tan(angle / 2);
  this->direction  = this->direction.normalized() * dirLen;
}

const Vector3 & Camera::getLocation() const
{
  return this->location;
}
const Vector3 & Camera::getDirection() const
{
  return this->direction;
}
const Vector3 & Camera::getRight() const
{
  return this->rightVec;
}
const Vector3 & Camera::getUp() const
{
  return this->upVec;
}
/**
 * Pivot direction, up,and right
 * to look at the  vector.
 */
void Camera::init()
{
  if(!initLookAt)
  {
    this->look_at = this->location + Vector3(0,0,1);
  }

  this->direction = (this->look_at - this->location).normalized() * direction.norm();
  this->upVec = 
    (this->sky - Maths::project(this->sky,this->direction)) * this->upVec.norm();
  this->rightVec =  (direction.cross(upVec)).normalized() * this->rightVec.norm();


}