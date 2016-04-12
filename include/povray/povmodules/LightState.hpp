#ifndef __LIGHT_STATE_H__
#define __LIGHT_STATE_H__
#include "ParseState.hpp"
class LightState : public ParseState{
   /**
    * The Camera state attempts
    * to read in the pov format for a camera,
    * and transitioning back to the base state for
    * additional processing.
    */
public:
   std::string toString();
   ParseState * accept(std::istream & token);
};
#endif