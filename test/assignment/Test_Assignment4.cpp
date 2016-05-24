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

TEST_CASE("Assignment 4" , "[A4]")
{
   std::cout << "------Assignment 4------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/valentine2.pov");
   ReflectRefractRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>(),5);
   std::shared_ptr<TestLogger> logger = std::make_shared<TestLogger>();
   renderer.provideLogger(logger);
   renderer.setNSamples(1);
   renderer.cast(399, 280);
   renderer.cast(240, 280);
   logger->printLog(std::cout);
}

TEST_CASE("Andy", "[andy]")
{
   std::cout << "------Andy------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/simple.pov");
   ReflectRefractRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>(),5);
   std::shared_ptr<TestLogger> logger = std::make_shared<TestLogger>();
   renderer.provideLogger(logger);
   renderer.setNSamples(1);
   renderer.cast(300, 480-220);
   logger->printLog(std::cout);
}