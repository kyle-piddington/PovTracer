#include <catch/catch.hpp>
#include "geometry/Triangle.hpp"

TEST_CASE("Basic Triangle intersection", "[Triangle Intersection]")
{
   Triangle triangle(Vector3(-5,-5,0), Vector3(5,-5,0),Vector3(0,5,0));
   Ray ray(Vector3(0,0,-5),Vector3(0,0,1));
   Hit hit = triangle.intersect(ray, -1);
   REQUIRE(hit.didHit());
   REQUIRE(hit.getNormal() == Vector3(0,0,1));

   ray.direction = Vector3(1,0,0);
   hit = triangle.intersect(ray, -1);
   REQUIRE(!hit.didHit());
        
}
TEST_CASE("Tilted Triangle intersection" , "[Triangle Intersection]")
{
   Triangle triangle(Vector3(-5,-5,0), Vector3(5,-5,-5),Vector3(0,5,-5));
   Ray ray(Vector3(0,0,-5),Vector3(0,0,1));
   Hit hit = triangle.intersect(ray, -1);
   REQUIRE(hit.didHit());
}

