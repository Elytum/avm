#include <invalid_file.hpp>

const char * InvalidFile::what() const throw ()
{
	return "Error : invalid file";
}