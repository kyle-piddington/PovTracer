#include "povray/povmodules/ObjectModifierState.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "povray/PovUtil.hpp"
#include "camera/Camera.hpp"
#include "math/Transform.hpp"
ObjectModifierState::ObjectModifierState():
   geometry(nullptr)
   {

   }
ObjectModifierState::ObjectModifierState(IGeometry * object)
   {
      setObject(object);
   }

   
/**
 * The camera state looks like the following:
 */
ParseState * ObjectModifierState::accept(std::istream & stream)
{
   std::string bfr;
   bool setTransform;

   stream >> bfr;
   if(geometry == nullptr)
   {
      throw ParseException(bfr, "Object modifier state entered without an object!");
      
   }
   if(bfr.find("}") == std::string::npos || PovUtil::isComment(bfr))
   {
      std::cout << bfr << std::endl;
      
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
         setTransform = true;
         cTransform = 
            Transform::createTranslationMatrix(PovUtil::readVec3(stream)) * cTransform;
         return this;
      }
      else if(bfr == "rotate")
      {
         setTransform = true;
         cTransform = 
            Transform::createRotationMatirx(PovUtil::readVec3(stream)) * cTransform;
         return this;
      }
      else if(bfr == "scale")
      {
         setTransform = true;
         cTransform = Transform::createScaleMatrix(PovUtil::readVec3(stream)) * cTransform;
         return this;
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
   geometry->setTransform(cTransform);
   return transition(&PovStates::baseState);
}

void ObjectModifierState::setObject(IGeometry * object)
{
   std::cout << "Set object" << std::endl;
   cTransform = Matrix4::Identity();
   this->geometry = object;
}
std::string ObjectModifierState::toString()
{
   return "ObjectModifierState";
}
