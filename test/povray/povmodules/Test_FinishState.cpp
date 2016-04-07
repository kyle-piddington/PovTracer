#include "povray/povmodules/FinishState.hpp"
#include <catch/catch.hpp>
#include <sstream>

TEST_CASE("Read finish state","[Parse]")
{
   std::string test =
   "{\n\
      ambient 1.0\n\
      diffuse 1.0\n\
      specular 1.0\n\
      //{}Comment thy code!{}\n\
      roughness 1.0\n\
      reflection 1.0\n\
      refraction 1.0\n\
      ior 0.0\n\
   }";
   std::stringstream stream;
   stream << test;
   Finish finish;
   FinishState state(&finish, nullptr);
   state.accept(stream);
   REQUIRE(finish.getAmbient() == Amount(1.0));
   REQUIRE(finish.getDiffuse() == Amount(1.0));
   REQUIRE(finish.getSpecular() == Amount(1.0));
   REQUIRE(finish.getRoughness() == Amount(1.0));
   REQUIRE(finish.getRefraction() == Amount(1.0));
   REQUIRE(finish.getRefraction() == Amount(1.0));
   REQUIRE(finish.getIor() == Amount(0.0));
}


TEST_CASE("Finish state called without setting finish", "[Parse]")
{
    std::string test =
   "{\n\
      ambient 1.0\n\
      diffuse 1.0\n\
      specular 1.0\n\
      //{}Comment thy code!{}\n\
      roughness 1.0\n\
      reflection 1.0\n\
      refraction 1.0\n\
      ior 0.0\n\
   }";
   std::stringstream stream;
   stream << test;

   FinishState state;
   REQUIRE_THROWS(state.accept(stream));
}