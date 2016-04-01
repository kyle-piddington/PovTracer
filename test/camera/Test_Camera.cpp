#include <catch/catch.hpp>
#include <camera/Camera.hpp>
#include "Precision.hpp"
TEST_CASE("Default Camera","[Camera]")
{
   Camera cam;
   cam.init();
   REQUIRE(cam.getLocation() == Vector3(0,0,0));
   REQUIRE(cam.getDirection() == Vector3(0,0,1));
   REQUIRE(cam.getUp() == Vector3(0,1,0));
   REQUIRE(cam.getRight() == Vector3(1.33,0,0));

}
TEST_CASE("Turned Camera","[Camera]")
{
   Camera cam;
   cam.setLookAt(Vector3(1,0,0));
   cam.init();
   REQUIRE(cam.getLocation() == Vector3(0,0,0));
   REQUIRE(cam.getDirection() == Vector3(1,0,0));
   REQUIRE(cam.getUp() == Vector3(0,1,0));
   //Right should out of the scene
   REQUIRE(cam.getRight() == Vector3(0,0,-1.33));

}
TEST_CASE("Tilted Camera","[Camera]")
{
   Camera cam;
   cam.setLookAt(Vector3(0,1,1));
   cam.init();
   REQUIRE(cam.getLocation() == Vector3(0,0,0));
   REQUIRE(cam.getDirection() == Vector3(0,sqrt(2)/2,sqrt(2)/2));
   REQUIRE(cam.getUp() == Vector3(0,0.5,-0.5));
   REQUIRE(cam.getRight() == Vector3(1.33,0,0));

}