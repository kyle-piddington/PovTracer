#include "povray/povmodules/LightSourceState.hpp"
#include "povray/PovUtil.hpp"
#include "povray/povmodules/PovStates.hpp"

ParseState * LightSourceState::accept(std::istream & stream)
{
   std::string bfr;
   stream >> bfr; //Read '{''
   stream >> bfr;
   //@TODO: parsing!
   while(bfr.find("}") == std::string::npos || PovUtil::isComment(bfr))
   {
      stream >> bfr;

   }

   return transition(&PovStates::baseState);
}

std::string LightSourceState::toString()
{
   return "LightSourceState";
}