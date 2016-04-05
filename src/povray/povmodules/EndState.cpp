#include "povray/povmodules/EndState.hpp"

ParseState * EndState::accept(std::stringstream & token)
{
   token.str(std::string());
   token.clear();
   return this;
   //throw ParseException(token.str(),"Accept called on end state");
}

std::string EndState::toString()
{
   return "EndState";
}
