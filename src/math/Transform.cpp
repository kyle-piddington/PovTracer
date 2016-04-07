#include "math/Transform.hpp"
#include <iostream>
#include "math/Maths.hpp"
#include "scene/World.hpp"



Transform::Transform():
   position(Vector3(0,0,0)),
   rotation(Maths::quatFromEuler(Vector3(0,0,0))),
   scale(Vector3(1,1,1)),
   localUp(Vector4(World::Up[0],World::Up[1],World::Up[2],0.0)),
   localRight(Vector4(World::Right[0],World::Right[1],World::Right[2],0.0)),
   localForward(Vector4(World::Forward[0],World::Forward[1],World::Forward[2],0.0)),
   currentMatrix(),
   isDirty(false),
   parent(nullptr)
   {
      currentMatrix.setIdentity();
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

void Transform::setRotation(float angle, Vector3 axis)
{
   //Assert axis greater than zero
   
   if(axis.norm() == 0)
   {
      assert(false);
   }
   axis.normalize();

   this->rotation = Eigen::AngleAxis<Amount>(angle,axis);

   isDirty = true;
   //glm::normalize(this->rotation);
   updateFrame();
}

void Transform::setRotation(const Quaternion & quat)
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
      Vector4 tmp = (getMatrix() * Vector4(pos.x(),pos.y(),pos.z(),0.0));
      transPosition = Vector3(tmp.x(),tmp.y(),tmp.z());
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
   
   this->rotation = (this->rotation * Maths::quatFromEuler(eulerAngles)).normalized();
   isDirty = true;
 
   updateFrame();
}

void Transform::rotate(float angle, const Vector3 & axis, Space::spaceType space)
{
   if(axis.norm() == 0)
   {
      assert(false);
   }
   //Convert world axis to local axis
   Vector3 localAxis = axis;
   if(space == Space::WORLD)
   {
      Matrix4 rotMtx = Maths::Matrix4_cast(rotation);
      Vector4 tmp = (rotMtx * Vector4(axis.x(),axis.y(),axis.z(),0.0));
      localAxis = Vector3(tmp.x(),tmp.y(),tmp.z());
   }
   localAxis.normalize();


   this->rotation = (this->rotation * Eigen::AngleAxis<Amount>(angle,localAxis)).normalized();
   isDirty = true;
 
   updateFrame();
}

Vector3 Transform::getPosition(Space::spaceType type) const
{
   if(type == Space::LOCAL || parent == nullptr)
      return position;
   else
      return (parent->getMatrix() * Vector4(position.x(),position.y(),position.z(),1.0)).segment<3>(0);
}
Quaternion Transform::getRotation() const
{
   return rotation;
}


const Matrix4 & Transform::getMatrix()
{
   if(isDirty)
   { 


      Matrix4 s; s <<   this->scale.x(),0,0,0,
                                 0,this->scale.y(),0,0,
                                 0,0,this->scale.z(),0,
                                 0,0,0,1;

      Matrix4 t; t<<             1,0,0,0,
                                 0,1,0,0,
                                 0,0,1,0,
                                 this->position.x(),this->position.y(),this->position.z(),1;
      currentMatrix =   t * Maths::Matrix4_cast(rotation) * s;
      isDirty = false;

   }
   if(parent != nullptr)
   {
      currentMatrix = parent->getMatrix() * currentMatrix;
   }
   return currentMatrix;
}


void Transform::setScale(Vector3 scale)
{
   this->scale = scale;
   isDirty = true;
}

Vector3 Transform::up(Space::spaceType type) const
{
   Vector3 vec =  localUp.segment<3>(0);
   if(type == Space::WORLD)
   {
      vec = (parent->getMatrix() * Vector4(vec.x(),vec.y(),vec.z(),0.0)).segment<3>(0);
   }
   return vec;
}

Vector3 Transform::right(Space::spaceType type) const
{
   Vector3 vec =  localRight.segment<3>(0);
   if(type == Space::WORLD)
   {
      vec = (parent->getMatrix() * Vector4(vec.x(),vec.y(),vec.z(),0.0)).segment<3>(0);
   }
   return vec;
}

Vector3 Transform::forward(Space::spaceType type) const
{
   Vector3 vec =  localForward.segment<3>(0);
   if(type == Space::WORLD)
   {
      vec = (parent->getMatrix() * Vector4(vec.x(),vec.y(),vec.z(),0.0)).segment<3>(0);
   }
   return vec;
}

Vector3 Transform::getScale() const
{
   return scale;
}
void Transform::updateFrame()
{

   Vector4 wUp; wUp << World::Up,0.0;
   Vector4 wRt; wRt << World::Right,0.0;
   Vector4 wFw; wFw << World::Forward,0.0;
   Matrix4 rotMtx = Maths::Matrix4_cast(rotation);
   localRight = (rotMtx * wRt).normalized();
   localUp = (rotMtx * wUp).normalized();
   localForward = (rotMtx * wFw).normalized();


}

void Transform::setIdentity()
{
   position = (Vector3(0,0,0));
   rotation = Maths::quatFromEuler(Vector3(0,0,0));
   scale = (Vector3(1.0));
   localUp << World::Up,0.0 ;
   localRight <<  World::Right,0.0;
   localForward  << World::Forward,0.0;
   currentMatrix.setIdentity();
   isDirty = (true);
}
