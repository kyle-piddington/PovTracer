#ifndef __ENDSTATE_H__
#define __ENDSTATE_H__ 
#include "ParseState.hpp"
/**
 * The end state should never have accept called on
 * it. The only purpose is to be returned from
 * the base state.
 */
class EndState : public ParseState
{

public:
   ParseState * accept(std::istream & token);
   std::string toString();
};
#endif
