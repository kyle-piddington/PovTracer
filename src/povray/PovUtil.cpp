#include "povray/PovUtil.hpp"
#include "povray/ParseException.hpp"
#include "Precision.hpp"
bool PovUtil::isComment(const std::string & comment)
{
   if(comment.size() >= 2)
   {
      if(comment[0] == '/' && comment[1] == '/')
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      return false;
   }
}

void PovUtil::processComment(std::istream & istream)
{
   //Read until newline
   std::string bfr;
   std::getline(istream, bfr);
}
 
void checkStream(std::istream & stream, std::string err)
{
   if(stream.fail())
   {
      throw ParseException("--", err);
   }
}
Vector3 PovUtil::readVec3(std::istream & istream)
{
   Vector3 vector;
   char dummy;
   istream >> dummy;
   if(dummy != '<')
   {
      //Could be a single number, read back
      float scale;
      istream.unget();
      istream >> scale;
      checkStream(istream, "Could not parse vector, not single number or vector");
      vector << scale, scale, scale;
      return vector;

   }
   //Try to read out 3 floats
   istream >> vector[0];
   checkStream(istream, "Could not parse X");
   istream >> dummy; // Read ,
   istream >> vector[1];
   checkStream(istream, "Could not parse Y");
   istream >> dummy; //Read ,
   istream >> vector[2];
   checkStream(istream, "Could not parse Z");
   istream >> dummy; //Read >
   assert(dummy == '>');
   return vector;
}
Vector4 PovUtil::readVec4(std::istream & istream)
{
   Vector4 vector;
   char dummy;
   istream >> dummy; //Read <
   assert(dummy == '<');
   //Try to read out 3 floats
   istream >> vector[0];
   checkStream(istream, "Could not parse X");
   istream >> dummy; // Read ,
   istream >> vector[1];
   checkStream(istream, "Could not parse Y");
   istream >> dummy; //Read ,
   istream >> vector[2];
   checkStream(istream, "Could not parse Z");
   istream >> dummy; //Read ,
   istream >> vector[3];
   checkStream(istream, "Could not parse Z");
   
   istream >> dummy; //Read >
   assert(dummy == '>');
   return vector;
}