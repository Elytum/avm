#ifndef INVALID_FILE_HPP
#define INVALID_FILE_HPP

#include <exception>

class InvalidFile: public std::exception {
	virtual const char* what() const throw ();
};


#endif