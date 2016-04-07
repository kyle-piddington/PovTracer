#ifndef __PARSER_H__
#define __PARSER_H__
/**
 * The Povray Parser takes in a .pov file, validates, and 
 * returns a scene containing the geometry and cameras needed
 * to render  a scene. PovrayParser
 * also performs some validation and throws exceptions as neccesary
 */
#include <memory>
#include "scene/Scene.hpp"
#include <string>

class PovParser
{
public:
   static std::shared_ptr<Scene> CreateScene(std::string povFile);
   static std::shared_ptr<Scene> CreateScene(std::istream & file);
};
#endif