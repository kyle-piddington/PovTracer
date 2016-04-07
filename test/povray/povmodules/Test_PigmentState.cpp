#include "povray/povmodules/PigmentState.hpp"
#include <catch/catch.hpp>
#include <sstream>

TEST_CASE("Read rgb color","[Parse]")
{
   std::string test =std::string(
      "{ color rgb <0.2, 0.3, 0.8>\n\
         //And a comment for good measure\n\
       }");
   
   std::stringstream stream;
   stream << test;
   std::shared_ptr<IPigment> pigment;
   PigmentState state(&pigment, nullptr);
   state.accept(stream);
   Color4 col = pigment->getColor(Hit(Ray()));
   REQUIRE(col[0] == 0.2f);
   REQUIRE(col[1] == 0.3f);
   REQUIRE(col[2] == 0.8f);
   REQUIRE(col[3] == 0.0f);
}
TEST_CASE("Read rgbf 4 state","[Parse]")
{
   std::string test =
      "{ color rgbf <0.2, 0.3, 0.8, 0.5>\n\
         //And a comment for good measure\n\
       }";
   std::stringstream stream;
   stream << test;
   std::shared_ptr<IPigment> pigment = nullptr;
   PigmentState state(&pigment, nullptr);
   state.accept(stream);
   REQUIRE(pigment != nullptr);
   Color4 col = pigment->getColor(Hit(Ray()));
   REQUIRE(col[0] == 0.2f);
   REQUIRE(col[1] == 0.3f);
   REQUIRE(col[2] == 0.8f);
   REQUIRE(col[3] == 0.5f);
}

