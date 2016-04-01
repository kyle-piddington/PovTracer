#ifndef __PARSE_EXCEPTION_H__
#define __PARSE_EXCEPTION_H__
#include <string>
/**
 * A custom exception for
 * any errors that occurred during
 * the parse of a povray file.
 */
class ParseException : public std::exception
{
public:

   ParseException(std::string line, std::string err);
   const char *  what() const throw();

private:
   std::string line;
   std::string err;
};
#endif