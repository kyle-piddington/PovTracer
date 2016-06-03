#include "render/ReflectRefractRenderer.hpp"
#include "catch/catch.hpp"
#include "render/Renderer.hpp"
#include "shade/ColorPigment.hpp"
#include "material/PhongBRDF.hpp"
#include "material/LambertianBRDF.hpp"
#include "povray/PovParser.hpp"
#include "log/TestLogger.hpp"
#include <iostream>
#include <catch/catch.hpp>

TEST_CASE("Test Assignment 5-1","[Asgn3]")
{
   std::cout << "------Assignment 5------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/stress/recurses.pov");
   ReflectRefractRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>(),5);
   std::shared_ptr<TestLogger> logger = std::make_shared<TestLogger>();
   renderer.provideLogger(logger);
   renderer.setNSamples(1);
   renderer.cast(417, 303);
   logger->printLog(std::cout);
}
