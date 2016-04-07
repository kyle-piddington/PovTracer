#ifndef __PARSESTATE_H__
#define __PARSESTATE_H__
#include <sstream>
#include <istream>
#include "scene/Scene.hpp"
#include "povray/ParseException.hpp"
/**
 * A parse state is used
 * in parsing a pov file. The parse
 * state accepts some stream of input, consumes some
 * characters, and returns the next processing state.
 */
class ParseState
{
public:
  /**
   * Accept the incoming parsing stream, and
   * parse it.
   * @param  povFile The stream containing file data.
   * @return         a new state of parsing.
   */
   virtual ParseState * accept(std::istream & povFile) = 0;
   virtual std::string toString() = 0;
   void setScene(std::shared_ptr<Scene> scene);
protected:
   /**
    * Construct a parse state from nothing.
    */
   ParseState();

   /**
    * Construct a parse state with a scene.
    */
   ParseState(std::shared_ptr<Scene> scene);

   virtual ~ParseState();
   /**
    * Transition to a new Parse state.
    * @param  next the next state in the state machine
    * @return      the next state, with modifications
    *              to parent and currentScene
    */
   ParseState * transition(ParseState * next) const;

   std::shared_ptr<Scene> currentScene;


};
#endif