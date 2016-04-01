#include "povray/ParseException.hpp"

ParseException::ParseException(std::string line, std::string err):
   line(line),
   err(err)
{

}
const char * ParseException::what() const throw()
{
   std::string msg = "Error when parsing '" + line + "' : " + err;
   return msg.c_str();
}