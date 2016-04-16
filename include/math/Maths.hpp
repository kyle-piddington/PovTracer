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

   /**
    * Map one system of equations to another
    * @param  aMin  the min of one system
    * @param  aMax  the max of one system
    * @param  bMin  the min of another system
    * @param  bMax  the max of another system
    * @param  value the value to map in the first system.
    * @return       the value in the second system
    */
   Amount map(Amount aMin, Amount aMax, Amount bMin, Amount bMax, Amount value);

   Quaternion quatFromEuler(Vector3 euler);

   Matrix4 Matrix4_cast(const Quaternion & q);
}
#endif