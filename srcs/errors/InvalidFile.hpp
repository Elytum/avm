#ifndef INVALIDFILE_HPP
#define INVALIDFILE_HPP

#include <exception>

class InvalidFile: public std::exception {
	virtual const char* what() const throw ();
};


#endif