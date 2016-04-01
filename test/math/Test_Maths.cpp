#include "math/Maths.hpp"
#include <catch/catch.hpp>
TEST_CASE("Projection1","[Vectors]")
{
   Vector3 a(1,0,0);
   Vector3 b(2,1,0);
   Vector3 a1 = Maths::project(b,a);
   REQUIRE(a1.x() == 2.0);
   REQUIRE(a1.y() == 0);
   REQUIRE(a1.z() == 0);
   


}
TEST_CASE("Projection2","[Vectors]")
{
   Vector3 a(1,0,0);
   Vector3 b(0,1,0);
   Vector3 a1 = Maths::project(b,a);
   REQUIRE(a1.x() == 0.0);
   REQUIRE(a1.y() == 0);
   REQUIRE(a1.z() == 0);
   
   

}
TEST_CASE("Projection3","[Vectors]")
{
   Vector3 a(1,0,0);
   Vector3 b(1,0,0);
   Vector3 a1 = Maths::project(b,a);
   REQUIRE(a1.x() == 1.0);
   REQUIRE(a1.y() == 0);
   REQUIRE(a1.z() == 0);
   
   

}


