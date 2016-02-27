#include <Syntax.hpp>

const char * SyntaxError::what() const throw ()
{
	return "Error : Syntax error";
}