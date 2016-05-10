#include "math/Transform.hpp"
#include <catch/catch.hpp>
TEST_CASE("Translate","[Transform]")
{
   Matrix4 trns = Transform::createTranslationMatrix(Vector3(1,2,3));
   Matrix4 exp; exp << 1,0,0,1,
                       0,1,0,2,
                       0,0,1,3,
                       0,0,0,1;
   REQUIRE(trns == exp);
}
TEST_CASE("Rotate","[Set rotation]")
{
   Matrix4 rot = Transform::createRotationMatirx(Vector3(90,90,90));
}