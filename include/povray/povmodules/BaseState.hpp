#ifndef __BASE_STATE_H__
#define __BASE_STATE_H__
#include "ParseState.hpp"
class BaseState : public ParseState{
   /**
    * 
    */
public:
   std::string toString();
   ParseState * accept(std::istream & token);
};
#endif