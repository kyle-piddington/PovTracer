#include <catch/catch.hpp>
#include "povray/povmodules/SphereState.hpp"

TEST_CASE("Sphere Modifier", "[Parse]")
{
   std::shared_ptr<Scene> scene = std::make_shared<Scene>();
   std::string test =
       "{<0, 0, -1>, 2\n\
         finish  {ambient 0.2 diffuse 0.4}\n\
         pigment { color rgb <1.0, 0.0, 1.0>}\n\
   }\n";
   SphereState state;
   state.setScene(scene);
   std::stringstream stream;
   stream << test;
   auto next = state.accept(stream);
   next = next->accept(stream);
   next = next->accept(stream);
   next = next->accept(stream);
   next = next->accept(stream);

   Hit hit = scene->trace(Ray(Vector3(0,0,14), Vector3(0,0,-1)));
   REQUIRE(hit.didHit());
   REQUIRE(hit.getHitpoint() == Vector3(0,0,1));
   REQUIRE(hit.getGeometry()->getPigment()->getColor(hit) == Vector4(1.0,0.0,1.0,0.0));

}

