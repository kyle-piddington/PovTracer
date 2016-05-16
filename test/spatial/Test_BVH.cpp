#include <catch/catch.hpp>
#include "spatial/BVH.hpp"
#include "geometry/Sphere.hpp"

TEST_CASE("Empty init", "[BVH]")
{
   BVH tree;
   tree.init(std::vector<SceneObject>());
   Hit trace = tree.trace(Ray(Vector3(0,0,0),Vector3(0,0,1)));
   REQUIRE(trace.didHit() == false);
}
TEST_CASE("One object", "[BVH]")
{
   BVH tree;
   std::shared_ptr<IGeometry> geo = std::make_shared<Sphere>(Vector3(0,0,0), 3);
   SceneObject object(geo);
   std::vector<SceneObject> objs;
   objs.push_back(object);
   tree.init(objs);
   Hit trace = tree.trace(Ray(Vector3(0,0,14),Vector3(0,0,-1)));
   REQUIRE(trace.didHit() == true);

}
TEST_CASE("Several non-overlapping objects","[BVH]")
{
   BVH tree;
   std::vector<SceneObject> objs;
   for(int i = -10; i <= 10; i++)
   {
      std::shared_ptr<IGeometry> geo = std::make_shared<Sphere>(Vector3(0,0,i), 0.5);
      SceneObject object(geo);
      objs.push_back(object);
   }
   tree.init(objs);
   Hit trace = tree.trace(Ray(Vector3(0,0,11.5),Vector3(0,0,-1)));
   REQUIRE(trace.didHit() == true);
   REQUIRE(trace.getT() == 1);
}