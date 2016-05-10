#include <geometry/Sphere.hpp>
#include <base/Ray.hpp>
#include <catch/Catch.hpp>

TEST_CASE("Sphere Intersection 1", "[Sphere]")
{
   Ray ray(Vector3(0,0,1), Vector3(0,0,-1));
   Sphere sph(Vector3(0,0,-1),1.0);
   Hit h = sph.intersect(ray,0.0);
   REQUIRE(h.didHit());
   REQUIRE(h.getHitpoint() == Vector3(0,0,0));
   REQUIRE(h.getNormal() == Vector3(0,0,1));
   REQUIRE(h.getDistance() == 1.0);
}
TEST_CASE("Sphere Intersection 2 (glance)", "[Sphere]")
{
   Ray ray(Vector3(0,0,1), Vector3(0,0,-1));
   Sphere sph(Vector3(0,-1,-1),1.0);
   Hit h = sph.intersect(ray,0.0);
   REQUIRE(h.didHit());
   REQUIRE(h.getHitpoint() == Vector3(0,0,-1));
    REQUIRE(h.getNormal() == Vector3(0,1,0));
   REQUIRE(h.getDistance() == 2.0);
   
}
TEST_CASE("Sphere Intersection 3 (miss)", "[Sphere]")
{
   Ray ray(Vector3(0,0,1), Vector3(0,0,-1));
   Sphere sph(Vector3(0,10,-1),1.0);
   Hit h = sph.intersect(ray,0.0);
   REQUIRE(!h.didHit());
   
}

TEST_CASE("Sphere Intersection 4 (internal)", "[Sphere]")
{
   Ray ray(Vector3(0,0,1), Vector3(0,0,-1));
   Sphere sph(Vector3(0,0,0),100.0);
   Hit h = sph.intersect(ray,0.0);
   REQUIRE(h.didHit());
   REQUIRE(h.getNormal() == Vector3(0,0,-1));

   
}


