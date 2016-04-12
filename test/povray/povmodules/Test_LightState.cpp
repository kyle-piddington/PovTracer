#include <catch/catch.hpp>
#include "povray/povmodules/LightState.hpp"

TEST_CASE("Parsing a light state", "[Parse]")
{
   std::string test = "{<-100, 100, 100> color rgb <1.5, 1.5, 1.5>}";
   std::stringstream str;
   str << test;
   auto scene = std::make_shared<Scene>();
   LightState state;
   state.setScene(scene);
   state.accept(str);
   REQUIRE(scene->getLights().size() == 1);
   REQUIRE(scene->getLights()[0].getPosition() == Vector3(-100,100,100));
   REQUIRE(scene->getLights()[0].getColor() == Vector4(1.5,1.5,1.5,1.0));
   

}