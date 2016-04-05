#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include "Precision.hpp"
namespace Space
{
  enum spaceType
  {
    WORLD = 0,
    LOCAL = 1
  };
}
class Transform
{
public:
   Transform();
   Transform(const Transform & other);
   /**
    * Set the position of the transform
    * @param pos position to go to
    */
   void setPosition(const Vector3 & pos);

   /**
    * Copy a transform from another transofrm
    * @param other the transform to copy.
    */
   void copy(Transform & other);

   /**
    * Set the rotation of the transform
    * @param eulerAngles the angles to rotate to
    */
   void setRotation(const Vector3 & eulerAngles);

   /**
    * Set the rotation using Angle-Axis
    * @param angle the angle
    * @param axis  the axis to rotate on
    */
   void setRotation(Amount angle, const Vector3 & axis);

    /* Set the rotation using a straight quaternion
    * @param angle the angle
    * @param axis  the axis to rotate on
    */
   void setRotation(const glm::quat & q);
   /**
    * Move by a vector
    * @param pos the delta vector
    */
   void translate(const Vector3 & pos, Space::spaceType type = Space::WORLD);

   /**
    * Rotate by a set of angles
    * @param eulerAngles the new orientation to rotate to
    */
   void rotate(const Vector3 eulerAngles, Space::spaceType type = Space::WORLD);

    /**
    * Rotate by a set of angles
    * @param eulerAngles the new orientation to rotate to
    */
   void rotate(Amount angle, const Vector3 & axis, Space::spaceType type = Space::WORLD);
   
   /**
    * Orient the transform to point towards a target
    * @param target the target position
    */
   void lookAt(Vector3 target,Vector3 up = World::Up);

   /**
    * Orient the transform to point along a vector
    * @param forward the new forward vector
    * @param up      the world's up direction.
    */
   void lookAlong(Vector3 forward, Vector3 up = World::Up);

   /**
    * Scale the transform
    */
   void setScale(Vector3 scale);
   /**
    * Get the current position expressed as a 3d vector
    */
   Vector3 getPosition(Space::spaceType type = Space::WORLD) const;

   /**
    * Get the current rotation expressed as a quaternion
    * @return [description]
    */
   glm::quat getRotation() const;

   /**
    * Get the rotation expressed as euler angles
    * @return euler angle rotation
    */
   Vector3 getRotationEuler() const;

   /**
    * Get the scale of the transform
    */
   Vector3 getScale() const;

   /**
    * Get a 4x4 transform matrix representing this transform
    */
   const Matrix4 & getMatrix();

   Matrix4 getRotationMatrix();
   /**
    * Get the local up facing vector
    */
   Vector3 up(Space::spaceType space = Space::LOCAL) const;
   /**
    * Get the local right facing vector
    */
   Vector3 right(Space::spaceType space = Space::LOCAL) const;
   /**
    * Get the local forward facing vector
    */
   Vector3 forward(Space::spaceType space = Space::LOCAL) const;

   /*
   void setParent(Transform * parent)
   {
     this->parent = parent;
   }
   */

   void setIdentity();

private:
   void updateFrame();
   Vector3 position;
   Vector4 localUp;
   Vector4 localRight;
   Vector4 localForward;
   Vector3 scale;
   bool isDirty;
   Matrix4 currentMatrix;
   Quaternion rotation;
   Transform * parent;

};
#endif