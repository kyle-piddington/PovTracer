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
                     //Camera looks at 0,0,0\n\
                     look_at   <0, 0, 0>\n\
   }";
   std::stringstream file(test);
   auto scene = PovParser::CreateScene(file);
   auto camera = scene->getCamera();
   REQUIRE(camera.getLocation().z() == 14);


}


TEST_CASE("Full Scene setup","[Parser]")
{
   std::string test =
   "// cs174, assignment 1 sample file (RIGHT HANDED)\n\
\n\
     camera {\n\
     location  <0, 0, 14>\n\
     up        <0,  1,  0>\n\
     right     <1.33333, 0,  0>\n\
     look_at   <0, 0, 0>\n\
   }\n\
\n\
\n\
   light_source {<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}\n\
\n\
   sphere { <0, 0, 0>, 2\n\
     pigment { color rgb <1.0, 0.0, 1.0>}\n\
     finish {ambient 0.2 diffuse 0.4}\n\
     translate <0, 0, 0>\n\
   }\n\
\n\
   plane { <0, 1, 0>, -4\n\
         pigment {color rgb <0.2, 0.2, 0.8>}\n\
         finish {ambient 0.4 diffuse 0.8}\n\
   }\n";

   std::stringstream file(test);
   auto scene = PovParser::CreateScene(file);
   auto camera = scene->getCamera();
   REQUIRE(camera.getLocation().z() == 14);
   REQUIRE(camera.getDirection().z() == -1);

   Hit hit = scene->trace(camera.getRay(0,0));
   REQUIRE(hit.didHit());
   REQUIRE(hit.getHitpoint() == Vector3(0,0,2));
   REQUIRE(hit.getGeometry()->getPigment()->getColor(hit) == Vector4(1.0,0.0,1.0,0.0));

   hit = scene->trace(camera.getRay(0,-0.5));
   REQUIRE(hit.didHit());
   REQUIRE(hit.getGeometry()->getPigment()->getColor(hit) == Vector4(0.2,0.2,0.8,0.0));

}
