#pragma once
#include "Precision.hpp"
namespace Transform
{
  /**
   * Create a translation matrix out of a Vector3
   */
   Matrix4 createTranslationMatrix(const Vector3 & tranlsation);

   /**
    * Create a rotation matrix out of a Vector3
    */
   Matrix4 createRotationMatirx(const Vector3 & eulerAngles);

   /**
    * Create a scale matrix out of a Vector3
    */
   Matrix4 createScaleMatrix(const Vector3 & scale);

};