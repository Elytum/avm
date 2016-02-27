#ifndef OVERFLOW_CPP
# define OVERFLOW_CPP

#include <exception>

class Overflow : public std::exception {
	virtual const char* what() const throw ();
};

#endif