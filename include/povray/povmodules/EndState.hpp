#include "ParseState.hpp"
/**
 * The end state should never have accept called on
 * it. The only purpose is to be returned from
 * the base state.
 */
class EndState : public ParseState
{

public:
   ParseState * accept(std::stringstream & token);
   std::string toString();
};