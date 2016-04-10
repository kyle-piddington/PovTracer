#include "povray/povmodules/PlaneState.hpp"

PlaneState::PlaneState()
{

}

ParseState * PlaneState::accept(std::istream & stream)
{
   //Read '{'
   char bfr;
   token >> bfr;
   
   Plane * plane = &(*currentScene->addSphere());
   //Read vec3
   Vector3 norm = PovUtil::readVec3(token);

   //Read ','
   token >> bfr;
   //Read Radius
   Amount dist;
   token >> dist;
   if(token.fail())
   {
      throw ParseException("--", "Could not read float from plane state");
   }
   *plane = Plane(norm,dist);
   //Set up the next state
   PovStates::objectState = ObjectModifierState(plane);
   return &PovStates::objectState;
}

std::string PlaneState::toString()
{
   return "PlaneState"
}
