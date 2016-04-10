#include "povray/povmodules/PigmentState.hpp"
#include "povray/PovUtil.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "shade/ColorPigment.hpp"
PigmentState::PigmentState():
   pigmentPtr(nullptr),
   parent(nullptr)
   {

   }
PigmentState::PigmentState(std::shared_ptr<IPigment> * ptr, ParseState * parent):
   pigmentPtr(ptr),
   parent(parent)
   {

   }

void PigmentState::processColorPigment(std::istream & stream)
{

   std::string type;
   stream >> type;
   if(type == "rgb")
   {
      Color3 col = PovUtil::readVec3(stream);
      *pigmentPtr = std::shared_ptr<IPigment>(
                     std::make_shared<ColorPigment>(col));

   }
   else if(type == "rgbf")
   {
      Color4 col = PovUtil::readVec4(stream);
      *pigmentPtr = std::shared_ptr<IPigment>(
                     std::make_shared<ColorPigment>(col));   }
   else
   {
      throw ParseException(type, "Unsupported state for Pigment Color");
   }

}

ParseState * PigmentState::accept(std::istream & stream)
{
   std::string bfr;
   char cBuffer;
   Amount numBuffer;
   stream >> cBuffer; //Read '{''
   stream >> bfr;
   while(bfr.find("}") == std::string::npos || PovUtil::isComment(bfr))
   {
      if(PovUtil::isComment(bfr))
      {
         PovUtil::processComment(stream);
      }
      else if(bfr == "color")
      {
         processColorPigment(stream);
      }
      else
      {
         throw ParseException(bfr, "Unsupported state for Pigment");
      }
      stream >> bfr;
   }
   if(parent != nullptr)
   {
      return transition(parent);

   }
   else
   {
      return transition(&PovStates::endState);
   }
}
std::string PigmentState::toString()
{
   return "PigmentState";
}