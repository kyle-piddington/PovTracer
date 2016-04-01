#include "povray/povmodules/CameraState.hpp"
#include "povray/povmodules/PovStates.hpp"
#include "povray/PovUtil.hpp"
#include "camera/Camera.hpp"
/**
 * The camera state looks like the following:
 */
ParseState * CameraState::accept(std::stringstream & stream)
{
   Camera cam;
   std::string bfr;
   stream >> bfr; //Read '{''
   stream >> bfr;
   
   while(bfr.find("}") == std::string::npos)
   {
      if(PovUtil::isComment(bfr))
      {
         continue;
      }
      if(bfr == "location")
      {
         cam.setLocation(PovUtil::readVec3(stream));
      }
      else if(bfr == "up")
      {
         cam.setUp(PovUtil::readVec3(stream));
      }
      else if(bfr == "right")
      {
         cam.setRight(PovUtil::readVec3(stream));
      }
      else if(bfr == "look_at")
      {
         cam.setLookAt(PovUtil::readVec3(stream));
      }
      else
      {
         throw ParseException(bfr, "Unsupported state for camera");
      }
      stream >> bfr;
   
   }
   cam.init();
   currentScene->setCamera(cam);

   return transition(&PovStates::baseState);
}

std::string CameraState::toString()
{
   return "CameraState";
}