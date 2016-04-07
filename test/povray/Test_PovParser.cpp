#include "povray/PovParser.hpp"
#include <catch/catch.hpp>
TEST_CASE("Blank Parse","[Parser]")
{
   std::string test = 
   "";
   std::stringstream file(test);
   auto scene = PovParser::CreateScene(file);
   auto camera = scene->getCamera();
   REQUIRE(camera.getLocation() == Vector3(0,0,0));
   REQUIRE(camera.getDirection() == Vector3(0,0,1));
   



}

TEST_CASE("Setting up camera","[Parser]")
{
   std::string test =
   "//Testing a camera setup through the parser\n\
      camera {\n\
                     location  <0, 0, 14>\n\
                     look_at   <0, 0, 0>\n\
   }";
   std::stringstream file(test);
   auto scene = PovParser::CreateScene(file);
   auto camera = scene->getCamera();
   REQUIRE(camera.getLocation().z() == 14);


}
