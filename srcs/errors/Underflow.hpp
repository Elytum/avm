#ifndef UNDERFLOW_CPP
# define UNDERFLOW_CPP

#include <exception>
#include <string>

class Underflow : public std::exception {
	virtual const char* what() const throw ();
};

#endif