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
   REQUIRE(cam.getRight() == Vector3(-1.33,0,0));

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
   REQUIRE(cam.getRight() == Vector3(0,0,1.33));

}
TEST_CASE("180 Camera","[Camera]")
{
   Camera cam;
   cam.setLookAt(Vector3(0,0,-1));
   cam.init();
   REQUIRE(cam.getLocation() == Vector3(0,0,0));
   REQUIRE(cam.getDirection() == Vector3(0,0,-1));
   REQUIRE(cam.getUp() == Vector3(0,1,0));
   //Right should out of the scene
   REQUIRE(cam.getRight() == Vector3(1.33,0,0));

}
TEST_CASE("Tilted Camera","[Camera]")
{
   Camera cam;
   cam.setLookAt(Vector3(0,1,1));
   cam.init();
   REQUIRE(cam.getLocation() == Vector3(0,0,0));
   REQUIRE(cam.getDirection() == Vector3(0,sqrt(2)/2,sqrt(2)/2));
   REQUIRE(cam.getUp() == Vector3(0,0.5,-0.5));
   REQUIRE(cam.getRight() == Vector3(-1.33,0,0));

}

TEST_CASE("Generate Rays", "[Camera]")
{
   Camera cam;
   // -0.31138 -0.248958 -> d_x: -0.312988 d_y: -0.250522 d_z: -1
   cam.setLocation(Vector3(0,0,14));
   cam.setLookAt(Vector3(0,0,0));
   cam.init();
   Ray r1 = cam.getRay(320/640.0 - 0.5, 240/480.0 - 0.5);
   REQUIRE(r1.origin == Vector3(0,0,14));
   Vector3 ray1Dir = Vector3(0, 0, -1);
   //Require close to equal directions
   REQUIRE(r1.direction == ray1Dir);

}