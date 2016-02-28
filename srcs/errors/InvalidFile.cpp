#include <InvalidFile.hpp>

const char * InvalidFile::what() const throw ()
{
	return "Error : \033[1;31mInvalid file\033[0m";
}