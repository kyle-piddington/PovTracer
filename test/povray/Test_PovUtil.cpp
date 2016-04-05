#include <catch/catch.hpp>
#include "povray/PovUtil.hpp"
#include <sstream>
#include "Precision.hpp"
TEST_CASE("Comment detection","[Parse]")
{
   REQUIRE(PovUtil::isComment("//Hello world!"));
   REQUIRE(!PovUtil::isComment("Not Comment!"));
   REQUIRE(!PovUtil::isComment("/Not comment either"));
   REQUIRE(!PovUtil::isComment("/"));

}

TEST_CASE("Parsing Vec3", "[Parse]")
{
   std::string test("<1, 2.0, 3.3> <4, 5.5, 6.0>");
   std::stringstream stream;
   stream.str(test);
   Vector3 vec, vec2;
   REQUIRE_NOTHROW(vec = PovUtil::readVec3(stream));
   REQUIRE(vec.x() == 1.0f);
   REQUIRE(vec.y() == 2.0f);
   REQUIRE(vec.z() == 3.3f);
   REQUIRE_NOTHROW(vec2 = PovUtil::readVec3(stream));
   REQUIRE(vec2.x() == 4.0f);
   REQUIRE(vec2.y() == 5.5f);
   REQUIRE(vec2.z() == 6.0f);
}
TEST_CASE("Reading Comments", "[Parse]")
{
   std::stringstream str;
   str << "//Comment\nUncomment\n//Comment\nUnComment2";
   std::string readOut;
   str >> readOut;
   REQUIRE(PovUtil::isComment(readOut));
   PovUtil::processComment(str);
   str >> readOut;
   REQUIRE(readOut == "Uncomment");
   str >> readOut;
   REQUIRE(PovUtil::isComment(readOut));
   PovUtil::processComment(str);
   str >> readOut;
   REQUIRE(readOut == "UnComment2");
   str >> readOut;
   

   
   
}