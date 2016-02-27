#ifndef DIVISION_CPP
# define DIVISION_CPP

#include <exception>

class Division : public std::exception {
	virtual const char* what() const throw ();
};

#endif