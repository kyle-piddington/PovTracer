#include <catch/catch.hpp>
#include "geometry/Box.hpp"
#include "math/Transform.hpp"


TEST_CASE("Box intersection Test", "[Box]")
{
   Box box(Vector3(-1,-1,-1), Vector3(1,1,1));
   //Six intersecting sides
   Hit h1 = box.intersect(Ray(Vector3(0,0,10),Vector3(0,0,-1)),1);
   Hit h2 = box.intersect(Ray(Vector3(10,0,0),Vector3(-1,0,0)),1);
   Hit h3 = box.intersect(Ray(Vector3(0,10,0),Vector3(0,-1,0)),1);
   Hit h4 = box.intersect(Ray(Vector3(0,0,-10),Vector3(0,0,1)),1);
   Hit h5 = box.intersect(Ray(Vector3(-10,0,0),Vector3(1,0,0)),1);
   Hit h6 = box.intersect(Ray(Vector3(0,-10,0),Vector3(0,1,0)),1);
   
   REQUIRE(h1.didHit());
   REQUIRE(h2.didHit());
   REQUIRE(h3.didHit());
   REQUIRE(h4.didHit());
   REQUIRE(h5.didHit());
   REQUIRE(h6.didHit());

   REQUIRE(h1.getNormal() == Vector3(0,0,1));
   REQUIRE(h2.getNormal() == Vector3(1,0,0));
   REQUIRE(h3.getNormal() == Vector3(0,1,0));
   REQUIRE(h4.getNormal() == Vector3(0,0,-1));
   REQUIRE(h5.getNormal() == Vector3(-1,0,0));
   REQUIRE(h6.getNormal() == Vector3(0,-1,0));
   

}

TEST_CASE("Box internal intersection", "[Box]")
{
   Box box(Vector3(-1,-1,-1), Vector3(1,1,1));
   //Six intersecting sides
   Hit h1 = box.intersect(Ray(Vector3(0,0,0),Vector3(0,0,-1)),1);
   Hit h2 = box.intersect(Ray(Vector3(0,0,0),Vector3(-1,0,0)),1);
   Hit h3 = box.intersect(Ray(Vector3(0,0,0),Vector3(0,-1,0)),1);
   Hit h4 = box.intersect(Ray(Vector3(0,0,0),Vector3(0,0,1)),1);
   Hit h5 = box.intersect(Ray(Vector3(0,0,0),Vector3(1,0,0)),1);
   Hit h6 = box.intersect(Ray(Vector3(0,0,0),Vector3(0,1,0)),1);
   REQUIRE(h1.didHit());
   REQUIRE(h2.didHit());
   REQUIRE(h3.didHit());
   REQUIRE(h4.didHit());
   REQUIRE(h5.didHit());
   REQUIRE(h6.didHit());

   REQUIRE(h1.getNormal() == Vector3(0,0,-1));
   REQUIRE(h2.getNormal() == Vector3(-1,0,0));
   REQUIRE(h3.getNormal() == Vector3(0,-1,0));
   REQUIRE(h4.getNormal() == Vector3(0,0,1));
   REQUIRE(h5.getNormal() == Vector3(1,0,0));
   REQUIRE(h6.getNormal() == Vector3(0,1,0));
}

