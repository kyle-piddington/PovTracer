#include "povray/povmodules/BaseState.hpp"
#include <sstream>
#include <catch/catch.hpp>
SCENARIO("Base state accepts a stream","[Parse]")
{
   GIVEN("A base state")
   {
      BaseState bState;
      WHEN("An empty file is given")
      {
         std::stringstream file;
         file << "";
         auto next = bState.accept(file);
         THEN("The next state should be the End state")
         {
            REQUIRE(next->toString() == "EndState");
         }
      }
      WHEN("A file with a comment is given")
      {
         std::stringstream file;
         file << "//Hello! I am a comment.\n\
                  camera {\n\
                     location  <0, 0, 14>\n\
                     look_at   <0, 0, 0>\n\
                  }";
         auto next = bState.accept(file);
         THEN("The base state should be returned")
         {
            REQUIRE(next->toString() == "BaseState");
         }
      }
   }
}