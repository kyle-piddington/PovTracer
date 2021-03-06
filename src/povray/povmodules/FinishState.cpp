#include "povray/povmodules/FinishState.hpp"
#include "povray/PovUtil.hpp"
#include "povray/povmodules/PovStates.hpp"
FinishState::FinishState(Finish * finishObject, ParseState * parent):
   fObject(finishObject),
   parent(parent)
   {

   }
FinishState::FinishState():
   fObject(nullptr),
   parent(nullptr)
{

}
ParseState * FinishState::accept(std::istream & stream)
{



   std::string bfr;
   char cBuffer;
   Amount numBuffer;
   stream >> cBuffer; //Read '{'
   stream >> bfr;
   if(fObject == nullptr)
   {
      throw ParseException(bfr, "Finish state  called without setting finish object");
   }
   //While end not found and or is comment
   while(bfr.find("}") == std::string::npos  || PovUtil::isComment(bfr))
   {
      if(PovUtil::isComment(bfr))
      {
         PovUtil::processComment(stream);
         stream >> bfr;
         continue;
      }
      
      stream >> numBuffer;
      if(bfr == "ambient")
      {

         fObject->setAmbient(numBuffer);
      }
      else if(bfr == "diffuse")
      {
         fObject->setDiffuse(numBuffer);
      }
      else if(bfr == "specular")
      {
         fObject->setSpecular(numBuffer);
      }
      else if(bfr == "roughness")
      {
         fObject->setRoughness(numBuffer);
      }
      else if(bfr == "reflection")
      {

         fObject->setReflection(numBuffer);
      }
      else if(bfr == "refraction")
      {
         fObject->setRefraction(numBuffer);
      }
      else if(bfr == "ior")
      {
         fObject->setIor(numBuffer);
  
      }
      else
      {
         throw ParseException(bfr, "Unsupported state for Finish");
      }
      stream >> bfr;
   }
   //If Finish read more than it was supposed to,
   //reinstert characters into the stream.
   int backTrace = bfr.size() - 1;
   while(backTrace > 0)
   {
      stream.unget();
      backTrace --;
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
std::string FinishState::toString()
{
   return "FinishState";
}