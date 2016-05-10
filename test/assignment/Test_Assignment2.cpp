#include "render/SpecDiffuseBRDFRenderer.hpp"
#include "catch/catch.hpp"
#include "render/Renderer.hpp"
#include "shade/ColorPigment.hpp"
#include "material/PhongBRDF.hpp"
#include "material/LambertianBRDF.hpp"
#include "povray/PovParser.hpp"
#include <iostream>
#include <catch/catch.hpp>

TEST_CASE("Test Assignment 2","[Asgn2]")
{
   std::cout << "------Assignment 2------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/simple.pov");
   SpecDiffuseBRDFRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>());
   renderer.setNSamples(1);
   renderer.cast(120,120);
   std::cout << std::endl;
   renderer.cast(295,265);
   std::cout << std::endl;
   renderer.cast(420,130);

}