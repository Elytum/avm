#include <InvalidFile.hpp>

InvalidFile::InvalidFile() {

}

InvalidFile::~InvalidFile() {

}

InvalidFile::InvalidFile(InvalidFile const & src) {

}

InvalidFile::InvalidFile& operator=(InvalidFile const & rhs) {

}

const char * InvalidFile::what() const throw ()
{
	return "Error : \033[1;31mInvalid file\033[0m";
}