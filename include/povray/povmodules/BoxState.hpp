#pragma once
#include "ParseState.hpp"
class BoxState : public ParseState{
   
   /**
    * The triangle state parses a triangle object,
    * adds it to the scene, and then forwards
    * the object on to the rest of the parser.
    */
public:
   std::string toString();
   ParseState * accept(std::istream & token);
};