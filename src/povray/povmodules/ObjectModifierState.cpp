#include "povray/povmodules/ObjectModifierState.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "povray/PovUtil.hpp"
#include "camera/Camera.hpp"

ObjectModifierState::ObjectModifierState():
   geometry(nullptr)
   {

   }
ObjectModifierState::ObjectModifierState(IGeometry * object):
   geometry(object)
   {

   }

   
/**
 * The camera state looks like the following:
 */
ParseState * ObjectModifierState::accept(std::istream & stream)
{
   std::string bfr;
   stream >> bfr;
   if(geometry == nullptr)
   {
      throw ParseException(bfr, "Object modifier state entered without an object!");
      
   }
   if(bfr.find("}") == std::string::npos || PovUtil::isComment(bfr))
   {
      
      if(PovUtil::isComment(bfr))
      {
         PovUtil::processComment(stream);
      }
      else if(bfr == "finish")
      {
         PovStates::finishState = FinishState(geometry->getFinish(),this);
         return transition(&PovStates::finishState);
      }
      else if(bfr == "pigment")
      {
         PovStates::pigmentState = PigmentState(geometry->getPigmentPtr(),this);
         return transition(&PovStates::pigmentState);
      }
      else if(bfr == "translate")
      {
         PovUtil::readVec3(stream);
         return this;
         //cam.setRight(PovUtil::readVec3(stream));
      }
      else
      {
         throw ParseException(bfr, "Unsupported state for Modifier state");
      }
      stream >> bfr;
   
   }
   int backTrace = bfr.size() - 1;
   while(backTrace > 0)
   {
      stream.unget();
      backTrace --;
   }
   return transition(&PovStates::baseState);
}

void ObjectModifierState::setObject(IGeometry * object)
{
   this->geometry = object;
}
std::string ObjectModifierState::toString()
{
   return "ObjectModifierState";
}
