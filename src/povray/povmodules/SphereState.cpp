#include "povray/povmodules/SphereState.hpp"
#include "povray/PovUtil.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "geometry/Sphere.hpp"

SphereState::SphereState()
{

}

ParseState * SphereState::accept(std::istream & token)
{
   //Read '{'
   char bfr;
   token >> bfr;

   Sphere * sphere = &(* (currentScene->addSphere()));
   //Read vec3
   sphere->setPosition(PovUtil::readVec3(token));
   //Read ','
   token >> bfr;
   //Read Radius
   Amount rad;
   token >> rad;
   if(token.fail())
   {
      throw ParseException("--", "Could not read float from sphere state");
   }
   sphere->setRadius(rad);
   //Set up the next state
   PovStates::objectState = ObjectModifierState(sphere);
   return transition(&PovStates::objectState);
}

std::string SphereState::toString()
{
   return "SphereState";
}