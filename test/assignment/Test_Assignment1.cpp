#include "catch/catch.hpp"
#include "render/Renderer.hpp"
#include "render/FlatRenderer.hpp"
#include "shade/ColorPigment.hpp"
#include "povray/PovParser.hpp"
#include <iostream>

#define EPS 0.003
bool compareEps(Vector3 a, Vector3 b)
{
   if((b-a).norm() >= EPS)
   {
      std::cout << a << std::endl << "-----" << b << std::endl;
      return false;
   }
   return true;
}

void printTest(int px, int py, Hit & h, Renderer & r)
{
   std::cout << "(" << px << "," << py << ") -> ";
   std::cout << h.getRay() << std::endl
             << h << std::endl;
   if(h.didHit())
   {
      std::cout << "Color: "  << r.shade(h).transpose() << std::endl;
   }
   std::cout << std::endl;
}
TEST_CASE("Test Ray orientation","[Assignment 1]")
{

   std::shared_ptr<Scene> scene = std::make_shared<Scene>();
   Camera cam;
   cam.setLocation(Vector3(0,0,14));
   cam.setLookAt(Vector3(0,0,0));
   cam.init();

   scene->setCamera(cam);

   FlatRenderer renderer(640,480,scene);
   /**
    * {320, 240}
      {170, 120}
      {490, 120}
      {170, 360}
      {490, 360}
    */
   Ray r1 = renderer.getRayForPx(320,240);
   Vector3 r1Dir; r1Dir << 0,0,-1;
   REQUIRE(compareEps(r1.direction, r1Dir.normalized()));

   Ray r2 = renderer.getRayForPx(170,120);
   Vector3 r2Dir; r2Dir << -0.31138, -0.248958, -1;
   REQUIRE(compareEps(r2.direction, r2Dir.normalized()));

   Ray r3 = renderer.getRayForPx(490,120);
   Vector3 r3Dir; r3Dir <<  0.35512, -0.248958, -1;
   REQUIRE(compareEps(r3.direction, r3Dir.normalized()));

   Ray r4 = renderer.getRayForPx(170,360);
   Vector3 r4Dir; r4Dir << -0.31138, 0.251042, -1;
   REQUIRE(compareEps(r4.direction, r4Dir.normalized()));

   Ray r5 = renderer.getRayForPx(490,360);
   Vector3 r5Dir; r5Dir << 0.35512, 0.251042, -1;
   REQUIRE(compareEps(r5.direction, r5Dir.normalized()));
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

   FlatRenderer renderer(640,480,scene);


   //Should intersect w/ white sphere
   Ray r1 = renderer.getRayForPx(320,240);
   Hit h1 = scene->trace(r1);
   //Black sphere
   Ray r2 = renderer.getRayForPx(360,219);
   Hit h2 = scene->trace(r2);
   //Grey Sphere
   Ray r3 = renderer.getRayForPx(490,360);
   Hit h3 = scene->trace(r3);
   //Nothing
   REQUIRE(std::abs(h1.getDistance()  - 12.9902f) < EPS);
   REQUIRE(renderer.shade(h1) == Color4(1,1,1,0));

   REQUIRE(std::abs(h2.getDistance() - 13.7185f) < EPS);
   REQUIRE(renderer.shade(h2) == Color4(0,0,0,0));

   REQUIRE(!h3.didHit());

}
TEST_CASE("Test In Class" , "[Assignment 1]")
{
   /**
    * Scene setup
    */
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

   FlatRenderer renderer(640,480,scene);

   Ray r1 = renderer.getRayForPx(320,239);
   Hit h1 = scene->trace(r1);
   //Black sphere
   Ray r2 = renderer.getRayForPx(360,219);
   Hit h2 = scene->trace(r2);
   //Grey Sphere
   Ray r3 = renderer.getRayForPx(230,239);
   Hit h3 = scene->trace(r3);

   Ray r4 = renderer.getRayForPx(120, 349);
   Hit h4 = scene->trace(r4);

   Ray r5 = renderer.getRayForPx(490, 119);
   Hit h5 = scene->trace(r5);

   printTest(320,239, h1, renderer);
   printTest(360,219, h2, renderer);
   printTest(230,239, h3, renderer);
   printTest(120,349, h4, renderer);
   printTest(490,119, h5, renderer);

}

TEST_CASE("Planes test", "[Assignment 1]")
{
   std::shared_ptr<Scene> scene = PovParser::CreateScene("../assets/povray/planes.pov");
   FlatRenderer renderer(640,480,scene);

   Ray r1 = renderer.getRayForPx(320, 50);
   Hit h1 = scene->trace(r1);

   Ray r2 = renderer.getRayForPx(50, 240);
   Hit h2 = scene->trace(r2);

   Ray r3 = renderer.getRayForPx(590, 240);
   Hit h3 = scene->trace(r3);

   std::cout << "------Planes------" << std::endl;

   printTest(50,240, h2,renderer);
   printTest(320,50, h1,renderer);
   printTest(590,240,h3,renderer);



}