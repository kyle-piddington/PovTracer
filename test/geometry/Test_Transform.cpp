#include <geometry/Sphere.hpp>
#include <base/Ray.hpp>
#include <catch/Catch.hpp>

TEST_CASE("Transform Intersection Translation", "[Sphere]")
{
   Ray ray(Vector3(0,0,1), Vector3(0,0,-1));
   Sphere sph(Vector3(2,0,-1),1.0);
   //Sphere is transformed back to origin
   Matrix4 transformation;
   transformation << 1,0,0,-2,
                     0,1,0,0,
                     0,0,1,0,
                     0,0,0,1;
   sph.setTransform(transformation);
   Hit h = sph.intersectTransform(ray,9999);
   REQUIRE(h.didHit());
   REQUIRE(h.getHitpoint() == Vector3(0,0,0));
   REQUIRE(h.getNormal() == Vector3(0,0,1));
   REQUIRE(h.getDistance() == 1.0);
}
TEST_CASE("Transform Intersection Scale", "[Sphere]")
{
   Ray ray(Vector3(0,1,1), Vector3(0,0,-1));
   Sphere sph(Vector3(0,0,0),1.0);
   Matrix4 transformation;
  
   transformation <<  1,0,0,0,
                      0,2,0,0,
                      0,0,1   ,0,
                      0,0,0,1;
   Hit h = sph.intersectTransform(ray,9999);
   REQUIRE(h.didHit());
   REQUIRE(h.getHitpoint() == Vector3(0,1,0));
    REQUIRE(h.getNormal() == Vector3(0,1,0));
   REQUIRE(h.getDistance() == 1.0);
   
}


