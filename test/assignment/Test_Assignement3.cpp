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

TEST_CASE("Test Assignment 3-1","[Asgn3]")
{
   std::cout << "------Assignment 3------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/simple_reflect3.pov");
   ReflectRefractRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>(),5);
   std::shared_ptr<TestLogger> logger = std::make_shared<TestLogger>();
   renderer.provideLogger(logger);
   renderer.setNSamples(1);
   renderer.cast(320, 145);
   logger->printLog(std::cout);
}

TEST_CASE("Test Assignment 3-2","[Asgn3]")
{
   std::cout << "------Assignment 3------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/refract2.pov");
   ReflectRefractRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>(),5);
   std::shared_ptr<TestLogger> logger = std::make_shared<TestLogger>();
   renderer.provideLogger(logger);
   renderer.setNSamples(1);
   renderer.cast(315, 185);
   renderer.cast(220, 240);
   logger->printLog(std::cout);
}


TEST_CASE("Valentine", "[Asgn3]")
{
      std::cout << "------Valentine ------" << std::endl;
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/valentine2.pov");
   ReflectRefractRenderer renderer(640,480,scene, std::make_shared<LambertianBRDF>(),std::make_shared<PhongSpecularBRDF>(),5);
   std::shared_ptr<TestLogger> logger = std::make_shared<TestLogger>();
   renderer.provideLogger(logger);
   renderer.setNSamples(1);
   renderer.cast(421, 480-363);
   logger->printLog(std::cout);
}