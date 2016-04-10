#include <catch/catch.hpp>
#include "geometry/Plane.hpp"

TEST_CASE("Plane Intersection 1", "[Plane]")
{
   Ray ray(Vector3(0,1,0),Vector3(0,-1,0));
   Plane plane(Vector3(0,0,0),Vector3(0,1,0));
   Hit h = plane.intersect(ray);
   REQUIRE(h.didHit());
   REQUIRE(h.getHitpoint() == Vector3(0,0,0));
   REQUIRE(h.getDistance() == 1.0);
}

TEST_CASE("Plane Intersection 2", "[Plane]")
{
   Ray ray(Vector3(0,1,0),Vector3(0,-1,1));
   Plane plane(Vector3(0,0,0),Vector3(0,1,0));
   Hit h = plane.intersect(ray);
   REQUIRE(h.didHit());
   REQUIRE(h.getHitpoint() == Vector3(0,0,1));
   REQUIRE(h.getDistance() == (float)sqrt(2));
}

TEST_CASE("Plane Intersection 3", "[Plane]")
{
   Ray ray(Vector3(0,1,0),Vector3(1,0,1));
   Plane plane(Vector3(0,0,0),Vector3(0,1,0));
   Hit h = plane.intersect(ray);
   REQUIRE(!h.didHit());
}

TEST_CASE("Plane Intersection 4" , "[Plane]")
{
   Ray ray(Vector3(0,1,0),Vector3(1,1,1));
   Plane plane(Vector3(0,0,0),Vector3(0,1,0));
   Hit h = plane.intersect(ray);
   REQUIRE(!h.didHit());
}