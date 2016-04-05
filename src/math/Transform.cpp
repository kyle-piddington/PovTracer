#include "Transform.h"
#include <iostream>
#include "math/Maths.hpp"

#define GLM_FORCE_RADIANS

Transform::Transform():
   position(Vector3(0)),
   rotation(Vector3(0.0)),
   scale(Vector3(1.0)),
   localUp(Vector4(World::Up[0],World::Up[1],World::Up[2],0.0)),
   localRight(Vector4(World::Right[0],World::Right[1],World::Right[2],0.0)),
   localForward(Vector4(World::Forward[0],World::Forward[1],World::Forward[2],0.0)),
   currentMatrix(Matrix4(1.0)),
   isDirty(false),
   parent(nullptr)
   {
   }

Transform::Transform(const Transform & other):
   position(other.position),
   rotation(other.rotation),
   scale(other.scale),
   localUp(other.localUp),
   localRight(other.localRight),
   localForward(other.localForward),
   currentMatrix(other.currentMatrix),
   isDirty(other.isDirty),
   parent(other.parent)
   {
   }


void Transform::setPosition(const Vector3 & position)
{
   this->position = position;
   isDirty = true;
}

void Transform::setRotation(const Vector3 & eulerAngles)
{

   this->rotation = (Maths::quatFromEuler(Vector3(0.0)) * Maths::quatFromEuler(eulerAngles));
   isDirty = true;
   updateFrame();
}

void Transform::setRotation(float angle, const Vector3 & axis)
{
   //Assert axis greater than zero
   if(axis.length() == 0)
   {
      assert(false);
   }
   glm::normalize(axis);

   this->rotation = AngleAxis<Amount>(angle,axis);

   isDirty = true;
   //glm::normalize(this->rotation);
   updateFrame();
}

void Transform::setRotation(const glm::quat & quat)
{
   this->rotation = quat;
   isDirty = true;
   updateFrame();
}

void Transform::translate(const Vector3 & pos, Space::spaceType type)
{
   Vector3 transPosition = pos;
   if(type == Space::LOCAL)
   {
      transPosition = Vector3(getMatrix() * Vector4(pos,0.0));
   }
   this->position += transPosition;
   isDirty = true;
 

}

void Transform::copy(Transform & other)
{
   this->position = other.position;
   this->rotation = other.rotation;
   isDirty = true;
   updateFrame();
}

void Transform::rotate(const Vector3 eulerAngles, Space::spaceType type)
{
   
   this->rotation = glm::normalize(this->rotation * glm::quat(eulerAngles));
   isDirty = true;
 
   updateFrame();
}

void Transform::rotate(float angle, const Vector3 & axis, Space::spaceType space)
{
   if(axis.length() == 0)
   {
      assert(false);
   }
   //Convert world axis to local axis
   Vector3 localAxis = axis;
   if(space == Space::WORLD)
   {
      Matrix4 rotMtx = Matrix4_cast(rotation);
      localAxis = Vector3(rotMtx * Vector4(axis,0.0));
   }
   glm::normalize(localAxis);


   glm::quat newQuat = AngleAxis<Amount>(angle,localAxis);
   this->rotation = glm::normalize(this->rotation * newQuat);
   isDirty = true;
 
   updateFrame();
}

Vector3 Transform::getPosition(Space::spaceType type) const
{
   if(type == Space::LOCAL || parent == nullptr)
      return position;
   else
      return Vector3(parent->getMatrix() * Vector4(position,1.0));
}
glm::quat Transform::getRotation() const
{
   return rotation;
}

Vector3 Transform::getRotationEuler() const
{
   return glm::eulerAngles(rotation);
}
const Matrix4 & Transform::getMatrix()
{
   if(isDirty)
   { 


      Matrix4 s =    Matrix4(this->scale.x,0,0,0,
                                 0,this->scale.y,0,0,
                                 0,0,this->scale.z,0,
                                 0,0,0,1);

      Matrix4 t =    Matrix4(1,0,0,0,
                                 0,1,0,0,
                                 0,0,1,0,
                                 this->position.x,this->position.y,this->position.z,1);
      currentMatrix =   t * Matrix4_cast(rotation) * s;
      isDirty = false;

   }
   if(parent != nullptr)
   {
      currentMatrix = parent->getMatrix() * currentMatrix;
   }
   return currentMatrix;
}

void Transform::lookAt(Vector3 target, Vector3 upVec)
{
   /*Vector forward = lookAt.Normalized();
   Vector right = Vector::Cross(up.Normalized(), forward);
   Vector up = Vector::Cross(forward, right);*/

   Vector3 forward = glm::normalize(target-position);
   Vector3 up = glm::orthonormalize(upVec, forward); // Keeps up the same, make forward orthogonal to up
   Vector3 right = glm::normalize(glm::cross(forward, up));

   Matrix4 rotMat;
   rotMat[0] = Vector4(right.x,right.y,right.z,0);
   rotMat[1] = Vector4(up.x, up.y, up.z, 0);
   rotMat[2] = Vector4(-forward.x, -forward.y, -forward.z, 0);
   rotMat[3] = Vector4(0,0,0,1);
   //Create a quaternion from the three vectors above.
   glm::quat ret = glm::quat_cast(rotMat);


   this->rotation = glm::normalize(ret);
   isDirty = true;
   updateFrame();



}
void Transform::lookAlong(Vector3 forward, Vector3 upVec)
{
   /*Vector forward = lookAt.Normalized();
   Vector right = Vector::Cross(up.Normalized(), forward);
   Vector up = Vector::Cross(forward, right);*/
   
   Vector3 up = glm::orthonormalize(upVec, forward); // Keeps up the same, make forward orthogonal to up
   Vector3 right = glm::normalize(glm::cross(forward, up));

   Matrix4 rotMat;
   rotMat[0] = Vector4(right.x,right.y,right.z,0);
   rotMat[1] = Vector4(up.x, up.y, up.z, 0);
   rotMat[2] = Vector4(-forward.x, -forward.y, -forward.z, 0);
   rotMat[3] = Vector4(0,0,0,1);
   //Create a quaternion from the three vectors above.
   glm::quat ret = glm::quat_cast(rotMat);


   this->rotation = glm::normalize(ret);
   isDirty = true;
   updateFrame();



}

void Transform::setScale(Vector3 scale)
{
   this->scale = scale;
   isDirty = true;
}

Vector3 Transform::up(Space::spaceType type) const
{
   Vector3 vec =  Vector3(localUp);
   if(type == Space::WORLD)
   {
      vec = Vector3(parent->getMatrix() * Vector4(vec,0.0));
   }
   return vec;
}

Vector3 Transform::right(Space::spaceType type) const
{
   Vector3 vec =  Vector3(localRight);
   if(type == Space::WORLD)
   {
      vec = Vector3(parent->getMatrix() * Vector4(vec,0.0));
   }
   return vec;
}

Vector3 Transform::forward(Space::spaceType type) const
{
   Vector3 vec =  Vector3(localForward);
   if(type == Space::WORLD)
   {
      vec = Vector3(parent->getMatrix() * Vector4(vec,0.0));
   }
   return vec;
}

Vector3 Transform::getScale() const
{
   return scale;
}
void Transform::updateFrame()
{

   Vector4 wUp(World::Up,0.0);
   Vector4 wRt(World::Right,0.0);
   Vector4 wFw(World::Forward,0.0);
   Matrix4 rotMtx = Matrix4_cast(rotation);
   localRight = glm::normalize(rotMtx * wRt);
   localUp = glm::normalize(rotMtx * wUp);
   localForward = glm::normalize(rotMtx * wFw);


}

void Transform::setIdentity()
{
   position = (Vector3(0));
   rotation = glm::quat(Vector3(0.0));
   scale = (Vector3(1.0));
   localUp = (Vector4(World::Up,0.0));
   localRight = (Vector4(World::Right,0.0));
   localForward = (Vector4(World::Forward,0.0));
   currentMatrix= (Matrix4(1.0));
   isDirty = (true);
}
