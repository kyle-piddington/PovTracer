#include "povray/povmodules/TriangleState.hpp"
#include "povray/PovUtil.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "geometry/Triangle.hpp"


ParseState * TriangleState::accept(std::istream & token)
{
   //Read '{'
   char bfr;
   token >> bfr;
   Vector3 vA = PovUtil::readVec3(token);
   //Read ','
   token >> bfr;

   Vector3 vB = PovUtil::readVec3(token);
   //Read ','
   token >> bfr;

   Vector3 vC = PovUtil::readVec3(token);
   Triangle * tri = &(*currentScene->addTriangle(vA, vB, vC));
   PovStates::objectState = ObjectModifierState(tri);
   return transition(&PovStates::objectState);
}

std::string TriangleState::toString()
{
   return "TriangleState";
}
