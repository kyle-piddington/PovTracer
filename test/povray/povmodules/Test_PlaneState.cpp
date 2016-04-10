#include <catch/catch.hpp>

#include "povray/povmodules/PlaneState.hpp"


TEST_CASE("Plane Modifier", "[Parse]")
{
   std::shared_ptr<Scene> scene = std::make_shared<Scene>();
   std::string test =
       "{<0, 1, 0>, -4\n\
         finish  {ambient 0.2 diffuse 0.4}\n\
         pigment { color rgb <1.0, 0.0, 1.0>}\n\
   }\n";
   PlaneState state;
   state.setScene(scene);
   std::stringstream stream;
   stream << test;
   auto next = state.accept(stream); //Accept plane
   next = next->accept(stream); //Finish
   next = next->accept(stream); //finish state
   next = next->accept(stream); //pigment
   next = next->accept(stream); //pigment state

   Hit hit = scene->trace(Ray(Vector3(0,0,14), Vector3(0,-1,0)));
   REQUIRE(hit.   didHit());
   REQUIRE(hit.getHitpoint() == Vector3(0,-4,14));
   REQUIRE(hit.getGeometry()->getPigment()->getColor(hit) == Vector4(1.0,0.0,1.0,0.0));

}

