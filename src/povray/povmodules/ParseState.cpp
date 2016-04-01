#include "povray/povmodules/ParseState.hpp"

ParseState::ParseState():
   currentScene(nullptr)
   {

   }

ParseState::ParseState(
   std::shared_ptr<Scene> scene):
   currentScene(scene)
{

}

ParseState::~ParseState()
{

}

void ParseState::setScene(std::shared_ptr<Scene> scene)
{
   this->currentScene = scene;
}
ParseState * ParseState::transition(ParseState * next) const
{
   next->currentScene = this->currentScene;
   return next;
}



