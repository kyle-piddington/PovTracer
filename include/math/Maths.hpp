#ifndef __MATHS_HPP__
#define __MATHS_HPP__
#include "Precision.hpp"
namespace Maths
{
   /**
    * Return the projection of V along U
    * @param  u the base vector
    * @param  v the vector to form the projection
    * @return   V projected on U
    */
   Vector3 project(Vector3 v, Vector3 u);

   Quaternion quatFromEuler(Vector3 euler);
}
#endif