#include "povray/PovUtil.hpp"
#include "povray/povmodules/PovStates.hpp"
ParseState * BaseState::accept(std::stringstream & stream)
{
   //Possible states for base to transition to
   //are the following:
   //Camera
   //Sphere
   //light_source
   //Plane
   if(!stream.str().empty())
   {
      std::string state;
      stream >> state;
      if(PovUtil::isComment(state))
      {
         PovUtil::processComment(stream);
         return this;
      }
      if(state.empty())
      {
         return transition(&PovStates::endState);
      }

      if(state == "camera")
      {
         return transition(&PovStates::cameraState);
      }
      else if(state == "light_source")
      {

      }
      else if(state == "sphere")
      {

      }
      else if(state == "plane")
      {

      }
      else
      {
         throw ParseException(state, "Unrecognized state for BaseState");
      }
   }
   else
   {
      return transition(&PovStates::endState);
   }
}
std::string BaseState::toString()
{
   return "BaseState";
}