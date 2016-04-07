#ifndef __ObjectModifier_STATE_H__
#define __ObjectModifier_STATE_H__
#include "ParseState.hpp"
#include "geometry/IGeometry.hpp"
class ObjectModifierState : public ParseState{
   /**
    * The ObjectModifier state attempts
    * to read in the pov format for an object's properties,
    */
public:
   /**
    * Construct an invalid ObjectModifier state
    */
   ObjectModifierState();
   /**
    * Construct a ObjectModifier state with an object to work on,
    * and a parse state to transition back to.
    */
   ObjectModifierState(IGeometry * object, ParseState * parent);
   
   /**
    * Read in a whole ObjectModifier stream, and return.
    * @param  token the stream to read
    * @return       the parent state.
    */
   ParseState * accept(std::stringstream & token);

   std::string toString();

private:
   ParseState * parent;
   IGeometry * geometry;
};
#endif