#ifndef __PLANE_STATE_H__
#define __PLANE_STATE_H__
#include "ParseState.hpp"
#include "ObjectModifierState.hpp"
#include "geometry/IGeometry.hpp"
class PlaneState : public ObjectModifierState{
   /**
    * The Plane state attempts
    * to read in the pov format for a Plane,
    * and transitions back to the base state.
    */
public:
   /**
    * Construct a Plane state
    */
   PlaneState();

   /**
    * Create a new plane, and begin parsing it.
    * @param  token the stream to read
    * @return       the parent state.
    */
   ParseState * accept(std::istream & token);

   std::string toString();

private:
   
};
#endif