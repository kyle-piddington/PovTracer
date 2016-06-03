#include "shade/Texture.hpp"
#include "catch/catch.hpp"

//Test Simple Sample
TEST_CASE("Sample 1 px", "[Texture]")
{
   stbi_uc bfr[] = {255,0,0};
   Texture t(1,1,3,bfr);
   Color3 col = t.sample(Vector2(0.5,0.5));
   REQUIRE((col - Color3(1,0,0)).norm() < kEpsilon);
}

TEST_CASE("Sample 4 px", "[Texture]")
{
   stbi_uc bfr[] = {255,0,0,
                    0, 0, 0,
                    0, 0, 0,
                    255, 0, 0};
   Texture t(2,2,3,bfr);
   Color3 col = t.sample(Vector2(0.5,0.5));
   REQUIRE((col - Color3(0.5,0,0)).norm() < kEpsilon);
   col = t.sample(Vector2(0.0,0.0));
   REQUIRE((col - Color3(1.0,0,0)).norm() < kEpsilon);
   col = t.sample(Vector2(1.0,1.0));
   REQUIRE((col - Color3(1.0,0,0)).norm() < kEpsilon);
}