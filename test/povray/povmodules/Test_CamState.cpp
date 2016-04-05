#include "povray/povmodules/CameraState.hpp"
#include <sstream>
#include <catch/catch.hpp>
#include "scene/Scene.hpp"
SCENARIO("Camera state accepts a stream","[Parse]")
{
   GIVEN("A camera state")
   {
      CameraState cState;
      auto scene = std::make_shared<Scene>();
      cState.setScene(scene);
      WHEN("A basic camera is read")
      {
         std::stringstream file;
         file << "{\n\
                     location  <0, 0, 14>\n\
                     look_at   <0, 0, 0>\n\
                  }";
         auto next = cState.accept(file);

         THEN("The Camera location should be set")
         {
            Vector3 loc = scene->getCamera().getLocation();
            REQUIRE(loc.x() == 0.f);
            REQUIRE(loc.y() == 0.f);
            REQUIRE(loc.z() == 14.f);

         }
         THEN("The Camera Direction should be set")
         {
            Vector3 dir = scene->getCamera().getDirection();
            REQUIRE(dir.x() == 0.f);
            REQUIRE(dir.y() == 0.f);
            REQUIRE(dir.z() == -1.f);
         }
      }
      WHEN("A camera with a comment is read")
      {
         std::stringstream file;
         file << "{\n\
                     location  <0, 0, 14>\n\
                     //{Hello world}\n\
                     look_at   <0, 0, 0>\n\
                  }";
         auto next = cState.accept(file);

         THEN("The comment should be ignored.")
         {
            Vector3 loc = scene->getCamera().getLocation();
            REQUIRE(loc.x() == 0.f);
            REQUIRE(loc.y() == 0.f);
            REQUIRE(loc.z() == 14.f);
            Vector3 dir = scene->getCamera().getDirection();
            REQUIRE(dir.x() == 0.f);
            REQUIRE(dir.y() == 0.f);
            REQUIRE(dir.z() == -1.f);

         }
        
      }
   }
}