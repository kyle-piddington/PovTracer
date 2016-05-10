#include "render/ReflectRefractRenderer.hpp"
#include "catch/catch.hpp"
#include "render/Renderer.hpp"
#include "shade/ColorPigment.hpp"
#include "material/PhongBRDF.hpp"
#include "material/LambertianBRDF.hpp"
#include "povray/PovParser.hpp"
#include <iostream>
#include <catch/catch.hpp>

TEST_CASE("Test Assignment 3","[Asgn3]")
{
   std::cout << "------Assignment 3------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/refract2.pov");
   ReflectRefractRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>(),5);
   renderer.setNSamples(1);
   renderer.cast(295, 265);
}