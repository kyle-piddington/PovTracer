#include "povray/PovUtil.hpp"
#include "povray/ParseException.hpp"
#include "Precision.hpp"
bool PovUtil::isComment(const std::string & comment)
{
   if(comment.size() > 2)
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

void checkStream(std::stringstream & stream, std::string err)
{
   if(stream.fail())
   {
      throw ParseException("--", err);
   }
}
Vector3 PovUtil::readVec3(std::stringstream & istream)
{
   Vector3 vector;
   char dummy;
   istream >> dummy; //Read <
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
   return vector;
}