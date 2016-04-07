#include "povray/PovParser.hpp"
#include <iostream>
#include <fstream>
#include "povray/ParseException.hpp"
#include "povray/povmodules/ParseState.hpp"
#include "povray/povmodules/BaseState.hpp"
#include "povray/povmodules/PovStates.hpp"


std::shared_ptr<Scene> parseScene(std::istream & buffer)
{
   std::shared_ptr<Scene> scenePtr = std::make_shared<Scene>();
   PovStates::SetScene(scenePtr);
   ParseState * cState = &PovStates::baseState;
   cState->setScene(scenePtr);
   while(!buffer.eof())
   {
      cState = cState->accept(buffer);
   }
   return scenePtr;

}
std::shared_ptr<Scene> PovParser::CreateScene(std::string povFile)
{
   std::ifstream file( povFile );
   if ( file )
   {
      std::stringstream buffer;
      buffer << file.rdbuf();
      file.close();
      return parseScene(buffer);
   }
   else
   {
      throw ParseException("--", "Could not open file");
   }
}

std::shared_ptr<Scene> PovParser::CreateScene(std::istream & bfr)
{
   return parseScene(bfr);
}

