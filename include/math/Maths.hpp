#ifndef __MATHS_HPP__
#define __MATHS_HPP__
#include "Precision.hpp"
#include <vector>
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

   /**
    * Calculate the fresnel term for two indicies
    * of refraction
    */
   Amount Fresnel0(Amount iorA, Amount iorb);

   /**
    * Random float between range
    */
   Amount randAmount(Amount min, Amount max);
   /**
    * Refract a ray through a surface
    * @param  iorA The index of refraction of the first surface
    * @param  iorB the index of refraction of the second surface
    * @param  d    The vector pointing towards the surface of intersection
    * @param  n    The normal of the surface, opposed to the d vecto
    * @return      The refracted vector
    */
   Vector3 refract(Amount iorA, Amount iorB, const Vector3  & d, const Vector3 & n);

   Quaternion quatFromEuler(Vector3 euler);

   Vector4 make_vec4(const Vector3 & vec3, Amount hCoord);

   Matrix4 Matrix4_cast(const Quaternion & q);

   Amount calculateShlicks(Amount iorA, Amount iorB, const Vector3 & rI, const Vector3 & n);

   Amount clamp(Amount min, Amount max, Amount val);
   /**
    * Generate a hemisphere sample with a square-root 
    * distribution
    * @param  nor   the normal to orient the sample on
    * @param  focus the amount to focus the sample. Higher = closer to noermal
    * @return       a new vector 3.
    */
   Vector3 generateHemisphereSample(const Vector3 & nor, Amount focus);
   
   void generateHemisphereSamples(const Vector3 & normal, Amount focus, int count, std::vector<Vector3> * sampleOut);


}
#endif