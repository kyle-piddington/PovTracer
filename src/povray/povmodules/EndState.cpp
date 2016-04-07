#include "povray/povmodules/EndState.hpp"

ParseState * EndState::accept(std::istream & token)
{
   return this;
   //throw ParseException(token.str(),"Accept called on end state");
}

std::string EndState::toString()
{
   return "EndState";
}
