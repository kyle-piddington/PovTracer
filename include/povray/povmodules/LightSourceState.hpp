#ifndef __LIGHTSOURCE_STATE_H__
#define __LIGHTSOURCE_STATE_H__
#include "ParseState.hpp"
/**
 *The Lightsource state is a temporary state
 *while I build in lighting.
 *
 * @TODO finish this!
 */
class LightSourceState : public ParseState
{

public:
   ParseState * accept(std::istream & token);
   std::string toString();
};

#endif
