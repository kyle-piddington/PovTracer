#include "povray/povmodules/LightState.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "povray/PovUtil.hpp"

std::string LightState::toString()
{
   return "LightState";
}

ParseState * LightState::accept(std::istream & stream)
{
   std::string bfr;
   char chrBfr;
   stream >> chrBfr;
   Vector3 lightPos = PovUtil::readVec3(stream);
   Vector3 lightColor = Vector3(1.0,1.0,1.0);
   while(bfr.find("}") == std::string::npos || PovUtil::isComment(bfr))
   {
      if(PovUtil::isComment(bfr))
      {
         PovUtil::processComment(stream);
      }
      if(bfr == "color")
      {
         //Read rgb
         stream >> bfr;
         lightColor = PovUtil::readVec3(stream);
      }
      stream >> bfr;

   }
   int backTrace = bfr.size() - 1;
   while(backTrace > 0)
   {
      stream.unget();
      backTrace --;
   }
   PointLight & light = currentScene->addPointLight();
   light.setPosition(lightPos);
   light.setColor(lightColor);
   return transition(&PovStates::baseState);

}