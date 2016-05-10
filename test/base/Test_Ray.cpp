#include <catch/catch.hpp>
#include <base/Ray.hpp>

TEST_CASE("Assignment and copy operators")
{
   Ray r1(Vector3(1,2,3),Vector3(4,5,6));
   Ray r2(r1);
   Ray r3;
   r3 = r1;
   REQUIRE(r2.origin == Vector3(1,2,3));
   REQUIRE(r2.direction == Vector3(4,5,6));
   REQUIRE(r3.origin == Vector3(1,2,3));
   REQUIRE(r3.direction == Vector3(4,5,6));

}