#include "math/Maths.hpp"

Vector3 Maths::project(Vector3 v, Vector3 u)
{
   return (u.dot(v)/u.dot(u)) * u;
}