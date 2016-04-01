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
   }
}