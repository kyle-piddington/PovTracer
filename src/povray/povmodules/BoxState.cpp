#include "povray/povmodules/BoxState.hpp"
#include "povray/PovUtil.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "geometry/Box.hpp"


ParseState * BoxState::accept(std::istream & token)
{
   //Read '{'
   char bfr;
   token >> bfr;

   Box * box = &(*(currentScene->addBox()));
   //Read vec3
   box->setMinCoords(PovUtil::readVec3(token));
   token >> bfr; //Read ','
   //read next vec
   box->setMaxCoords(PovUtil::readVec3(token));

   PovStates::objectState = ObjectModifierState(box);
   return transition(&PovStates::objectState);
}

std::string BoxState::toString()
{
   return "BoxState";
}