#include "scene/Scene.hpp"
void Scene::setCamera(const Camera & cam)
{
   this->camera = cam;
}

const Camera & Scene::getCamera()
{
   return this->camera;
}