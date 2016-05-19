#include <catch/catch.hpp>
#include "spatial/Octree.hpp"
#include "geometry/Sphere.hpp"


TEST_CASE("Empty Octree init", "[Octree]")
{
   Octree tree(5);
   tree.init(std::vector<SceneObject>());
   Hit trace = tree.trace(Ray(Vector3(0,0,0),Vector3(0,0,1)));
   REQUIRE(trace.didHit() == false);
}
TEST_CASE("Octree: One object", "[Octree]")
{
   Octree tree(5);
   std::shared_ptr<IGeometry> geo = std::make_shared<Sphere>(Vector3(0,0,0), 3);
   SceneObject object(geo);
   std::vector<SceneObject> objs;
   objs.push_back(object);
   tree.init(objs);
   Hit trace = tree.trace(Ray(Vector3(0,0,14),Vector3(0,0,-1)));
   REQUIRE(trace.didHit() == true);

}
TEST_CASE("Octree: eight objects", "[Octree]")
{
   Octree tree(5);
   std::vector<SceneObject> objs;
   for(int i = 0; i < 8; i++)
   {
      bool zBox = i%2;
      bool yBox = (i%4)/2;
      bool xBox = i/4;
      Vector3 offset = Vector3(xBox, yBox, zBox);
      std::shared_ptr<IGeometry> geo = std::make_shared<Sphere>(Vector3(-0.5,-0.5,-0.5) + offset , 0.5);
      SceneObject object(geo);
      objs.push_back(object);
   }
   tree.init(objs);
   //REQUIRE(tree.bounds.minCoords == Vector3(-1, -1, -1));
}
TEST_CASE("Octree: big Objects" , "[Octree]")
{
   Octree tree(5);
   std::vector<SceneObject> objs;
   objs.push_back(SceneObject(std::make_shared<Sphere>(Vector3(-0.5,-0.5,-0.5),1)));
   objs.push_back(SceneObject(std::make_shared<Sphere>(Vector3(0.5,0.5,0.5),1)));
   tree.init(objs);
}
/*
TEST_CASE("Octree: Several non-overlapping objects","[Octree]")
{
   Octree tree(5);
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

TEST_CASE("Octree: Many overlapping objects","[Octree]")
{
   Octree tree(5);
   std::vector<SceneObject> objs;
   for(int i = -50; i <= 50; i++)
   {
      std::shared_ptr<IGeometry> geo = std::make_shared<Sphere>(Vector3(i%25,i/25,0), 0.5);
      SceneObject object(geo);
      objs.push_back(object);
   }
   tree.init(objs);
   Hit trace = tree.trace(Ray(Vector3(0,0,11.5),Vector3(0,0,-1)));
   REQUIRE(trace.didHit() == true);
   REQUIRE(trace.getT() == 1);
}
*/