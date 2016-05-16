#include <catch/catch.hpp>
#include "spatial/BoundingBox.hpp"
#include "math/Transform.hpp"
TEST_CASE("BoundBox Transform Scale", "[Bounding Box]")
{
   BoundingBox box(Vector3(-1,-1,-1),Vector3(1,1,1));
   Matrix4 transformMat;
   transformMat << 2,0,0,0,
                   0,2,0,0,
                   0,0,2,0,
                   0,0,0,1;
   box = box.transform(transformMat);
   REQUIRE(box.minCoords == Vector3(-2,-2,-2));
   REQUIRE(box.maxCoords == Vector3(2,2,2));

}
TEST_CASE("BoundBox Transform Translate", "[Bounding Box]")
{
   BoundingBox box(Vector3(-1,-1,-1),Vector3(1,1,1));
   Matrix4 transformMat;
   transformMat << 1,0,0,1,
                   0,1,0,2,
                   0,0,1,3,
                   0,0,0,1;
   box = box.transform(transformMat);
   REQUIRE(box.minCoords == Vector3(0,1,2));
   REQUIRE(box.maxCoords == Vector3(2,3,4));

}
TEST_CASE("BoundBox Transform Rotate", "[Bounding Box]")
{
   BoundingBox box(Vector3(-1,-2,-1),Vector3(1,2,1));
   Matrix4 transformMat;
   transformMat << Transform::createRotationMatirx(Vector3(90,0,0));
   box = box.transform(transformMat);
   REQUIRE((box.minCoords - Vector3(-1,-1,-2)).norm() < kEpsilon);
   REQUIRE((box.maxCoords - Vector3(1,1,2)).norm() < kEpsilon);
}

TEST_CASE("BoundBox Transform Invalid", "[Bounding Box]")
{
   BoundingBox box = BoundingBox::Invalid();
   REQUIRE(!box.isValid());
   Matrix4 transformMat;
   transformMat << Transform::createRotationMatirx(Vector3(90,0,0));
   box = box.transform(transformMat);
   REQUIRE(!box.isValid());
}

TEST_CASE("Boundbox intersection Test", "[Bounding Box]")
{
   BoundingBox box(Vector3(-1,-1,-1), Vector3(1,1,1));
   //Six intersecting sides
   REQUIRE(box.intersect(AABB_Ray(Vector3(0,0,10),Vector3(0,0,-1))));
   REQUIRE(box.intersect(AABB_Ray(Vector3(10,0,0),Vector3(-1,0,0))));
   REQUIRE(box.intersect(AABB_Ray(Vector3(0,10,0),Vector3(0,-1,0))));
   REQUIRE(box.intersect(AABB_Ray(Vector3(0,0,-10),Vector3(0,0,1))));
   REQUIRE(box.intersect(AABB_Ray(Vector3(-10,0,0),Vector3(1,0,0))));
   REQUIRE(box.intersect(AABB_Ray(Vector3(0,-10,0),Vector3(0,1,0))));
   
   //Missing the box
   REQUIRE(!box.intersect(AABB_Ray(Vector3(0,0,10),Vector3(1,0,-1))));
   REQUIRE(!box.intersect(AABB_Ray(Vector3(10,0,0),Vector3(-1,1,0))));
   REQUIRE(!box.intersect(AABB_Ray(Vector3(0,10,0),Vector3(1,-1,0))));

   //Negative box
   REQUIRE(!box.intersect(AABB_Ray(Vector3(0,0,10),Vector3(0,0,1))));


}

TEST_CASE("Boundbox centroid", "[Bounding box]")
{
   BoundingBox box(Vector3(0,0,0), Vector3(1,2,3));
   REQUIRE((box.centroid - Vector3(0.5, 1, 1.5)).norm() < kEpsilon);
}

TEST_CASE("BoundBox T values", "[Bounding box]")
{
   BoundingBox box(Vector3(-1,-1,-1), Vector3(1,1,1));
   //Six intersecting sides
   REQUIRE(9 == box.intersect(AABB_Ray(Vector3(0,0,10),Vector3(0,0,-1))));
  
}

TEST_CASE("BoundBox internal intersection", "[Bounding box]")
{
   BoundingBox box(Vector3(-1,-1,-1), Vector3(1,1,1));
   //Six intersecting sides
   REQUIRE(1 == box.intersect(AABB_Ray(Vector3(0,0,0),Vector3(0,0,-1))));
  
}

