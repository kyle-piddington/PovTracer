#include "povray/povmodules/PlaneState.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "geometry/Plane.hpp"
#include "povray/PovUtil.hpp"

PlaneState::PlaneState()
{

}

ParseState * PlaneState::accept(std::istream & stream)
{
   //Read '{'
   char bfr;
   stream >> bfr;

   Plane * plane = &(* (currentScene->addPlane()));
   //Read vec3
   Vector3 norm = PovUtil::readVec3(stream);

   //Read ','
   stream >> bfr;
   //Read Radius
   Amount dist;
   stream >> dist;
   if(stream.fail())
   {
      throw ParseException("--", "Could not read float from plane state");
   }
   *plane = Plane(norm,dist);
   //Set up the next state
   PovStates::objectState = ObjectModifierState(plane);
   return transition(&PovStates::objectState);
}

std::string PlaneState::toString()
{
   return "PlaneState";
}
