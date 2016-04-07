#ifndef __CAMERA_STATE_H__
#define __CAMERA_STATE_H__
#include "ParseState.hpp"
class CameraState : public ParseState{
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