#ifndef __Finish_STATE_H__
#define __Finish_STATE_H__
#include "ParseState.hpp"
#include "shade/Finish.hpp"
class FinishState : public ParseState{
   /**
    * The Finish state attempts
    * to read in the pov format for a Finish,
    * and transitioning back to the parent state for
    * additional processing.
    */
public:
   /**
    * Construct a finish state with an object to work on,
    * and a parse state to transition back to.
    */
   FinishState(Finish & finishObject, ParseState * parent);
   
   /**
    * Read in a whole finish stream, and return.
    * @param  token the stream to read
    * @return       the parent state.
    */
   ParseState * accept(std::stringstream & token);

   std::string toString();

private:
   ParseState * parent;
   Finish & fObject;
};
#endif