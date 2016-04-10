#include <catch/catch.hpp>
#include "povray/povmodules/ObjectModifierState.hpp"

TEST_CASE("Object Modifier", "[Parse]")
{
   Sphere sphere;
   std::string test = 
       "finish {ambient 0.2 diffuse 0.4}\n\
       pigment { color rgb <1.0, 0.0, 1.0>}\n\
   }\n";
   ObjectModifierState state(&sphere);
   std::stringstream stream;
   stream << test;
   auto nxt = state.accept(stream);
   nxt = nxt->accept(stream);
   nxt = nxt->accept(stream);
   nxt = nxt->accept(stream);

   Vector4 color = sphere.getPigment()->getColor(Hit(Ray()));
   REQUIRE(color == Vector4(1,0,1,0));
   REQUIRE(sphere.getFinish()->getAmbient() == 0.2f);
   REQUIRE(sphere.getFinish()->getDiffuse() == 0.4f);
}

