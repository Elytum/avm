#ifndef OVERFLOW_CPP
# define OVERFLOW_CPP

#include <exception>
#include <string>

class Overflow : public std::exception {
	virtual const char* what() const throw ();
};

#endif