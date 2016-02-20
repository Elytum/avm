#include <syntax.hpp>

const char * SyntaxError::what() const throw ()
{
	return "Error : syntax error";
}