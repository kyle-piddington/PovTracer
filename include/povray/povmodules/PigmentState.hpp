#ifndef __PIGMENT_STATE_H__
#define __PIGMENT_STATE_H__
#include "ParseState.hpp"
#include "shade/IPigment.hpp"
class PigmentState : public ParseState{
   /**
    * The Pigment state attempts
    * to read in the pov format for a Pigment,
    * and transitions back to the parent state for
    * additional processing.
    */
public:
   /**
    * Construct a Pigment state with a pigment object
    * to work on, (The pigment pointer will be modified)
    * and a parse state to transition back to.
    */
   PigmentState(std::shared_ptr<IPigment> * pigment, ParseState * parent);

   PigmentState();

   /**
    * Read in a whole finish stream, and return.
    * @param  token the stream to read
    * @return       the parent state.
    */
   ParseState * accept(std::stringstream & token);


   std::string toString();

private:
   void processColorPigment(std::stringstream & stream);

   ParseState * parent;
   std::shared_ptr<IPigment> * pigmentPtr;
};
#endif