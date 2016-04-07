#include "catch/catch.hpp"
#include "render/Renderer.hpp"
#include "shade/ColorPigment.hpp"
#include <iostream>

#define EPS 0.002
bool compareEps(Vector3 a, Vector3 b)
{
   if((b-a).norm() >= EPS)
   {
      std::cout << a << std::endl << "-----" << b << std::endl;
      return false;
   }
   return true;
}
TEST_CASE("Test Ray orientation","[Assignment 1]")
{

   std::shared_ptr<Scene> scene = std::make_shared<Scene>();
   Camera cam;
   cam.setLocation(Vector3(0,0,14));
   cam.setLookAt(Vector3(0,0,0));
   cam.init();

   scene->setCamera(cam);

   Renderer renderer(640,480,scene);
   /**
    * {320, 240}
      {170, 120}
      {490, 120}
      {170, 360}
      {490, 360}
    */
   Ray r1 = renderer.getRayForPx(320,240);
   Vector3 r1Dir; r1Dir << 0,0,-1;
   REQUIRE(compareEps(r1.direction, r1Dir));

   Ray r2 = renderer.getRayForPx(170,120);
   Vector3 r2Dir; r2Dir << -0.31138, -0.248958, -1;
   REQUIRE(compareEps(r2.direction, r2Dir));

   Ray r3 = renderer.getRayForPx(490,120);
   Vector3 r3Dir; r3Dir <<  0.35512, -0.248958, -1;
   REQUIRE(compareEps(r3.direction, r3Dir));

   Ray r4 = renderer.getRayForPx(170,360);
   Vector3 r4Dir; r4Dir << -0.31138, 0.251042, -1;
   REQUIRE(compareEps(r4.direction, r4Dir));

   Ray r5 = renderer.getRayForPx(490,360);
   Vector3 r5Dir; r5Dir << 0.35512, 0.251042, -1;
   REQUIRE(compareEps(r5.direction, r5Dir));
}

TEST_CASE("Test Ray/Sphere collisions", "[Assignment 1]")
{
   std::shared_ptr<Scene> scene = std::make_shared<Scene>();
   Camera cam;
   cam.setLocation(Vector3(0,0,14));
   cam.setLookAt(Vector3(0,0,0));
   cam.init();

   scene->setCamera(cam);
   auto sph1 = scene->addSphere();
   sph1->setRadius(1.01);
   sph1->setPigment(ColorPigment::Create(Vector3(1,1,1)));

   auto sph2 = scene->addSphere();
   sph2->setPosition(Vector3(0,0,-1.5));
   sph2->setRadius(2.25);
   sph2->setPigment(ColorPigment::Create(Vector3(0,0,0)));

   auto sph3 = scene->addSphere();
   sph3->setPosition(Vector3(0,0,-4.5));
   sph3->setRadius(3.75);
   sph3->setPigment(ColorPigment::Create(Vector3(0.25,0.25,0.25)));

   auto sph4 = scene->addSphere();
   sph4->setPosition(Vector3(-5.5,3,-0));
   sph4->setRadius(1.1);
   sph4->setPigment(ColorPigment::Create(Vector3(0.12,0.34,0.56)));

   Renderer renderer(640,480,scene);


   //Should intersect w/ white sphere
   Ray r1 = renderer.getRayForPx(320,240);
   Hit h1 = scene->trace(r1);
   //Black sphere
   Ray r2 = renderer.getRayForPx(360,240);
   Hit h2 = scene->trace(r2);
   //Grey Sphere
   Ray r3 = renderer.getRayForPx(400,200);
   Hit h3 = scene->trace(r3);
   //Nothing
   Ray r4 = renderer.getRayForPx(170,360);
   Hit h4 = scene->trace(r4);
   //Blue sphere
   Ray r5 = renderer.getRayForPx(135,337);
   Hit h5 = scene->trace(r5);

   std::cout << "Ray 1: " << h1 << std::endl;
   std::cout << "    Color: " << h1.getGeometry()->shade(h1).transpose() << std::endl;
   std::cout << "Ray 2: " << h2 << std::endl;
   std::cout << "    Color: " << h2.getGeometry()->shade(h2).transpose() << std::endl;
   std::cout << "Ray 3: " << h3 << std::endl;
      std::cout << "    Color: " << h3.getGeometry()->shade(h3).transpose() << std::endl;
   std::cout << "Ray 4: " << h4 << std::endl;
   std::cout << "Ray 5: " << h5 << std::endl;
      std::cout << "    Color: " << h5.getGeometry()->shade(h5).transpose() << std::endl;
   


}