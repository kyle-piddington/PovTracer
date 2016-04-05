#include "base/Hit.hpp"
#include "geometry/IGeometry.hpp"
#include "base/Ray.hpp"

Hit::Hit():
   ray(nullptr),
   object(nullptr),
   hitGeometry(false)
{

}