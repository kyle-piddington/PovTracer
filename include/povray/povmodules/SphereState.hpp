#ifndef __Sphere_STATE_H__
#define __Sphere_STATE_H__
#include "ParseState.hpp"
#include "ObjectModifierState.hpp"
#include "geometry/IGeometry.hpp"
class SphereState : public ObjectModifierState{
   /**
    * The Sphere state attempts
    * to read in the pov format for a Sphere,
    * and transitions back to the base state.
    */
public:
   /**
    * Construct an invalid Sphere state
    */
   SphereState();

   /**
    * Read in a whole Sphere stream, and return.
    * @param  token the stream to read
    * @return       the parent state.
    */
   ParseState * accept(std::istream & token);

   std::string toString();

private:
   
};
#endif