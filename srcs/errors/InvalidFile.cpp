#include <InvalidFile.hpp>

const char * InvalidFile::what() const throw ()
{
	return "Error : Invalid file";
}