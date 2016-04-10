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
    * Construct a ObjectModifier state with an object to work on
    * After parsing finishes, the state returns to the base state.
    */
   ObjectModifierState(IGeometry * object);
   
   /**
    * Read in a whole ObjectModifier stream, and return.
    * @param  token the stream to read
    * @return       the parent state.
    */
   
   void setObject(IGeometry * object);
   
   ParseState * accept(std::istream & token);

   std::string toString();

private:

   IGeometry * geometry;
};
#endif