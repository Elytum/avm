#ifndef UNDERFLOW_CPP
# define UNDERFLOW_CPP

#include <exception>

class Underflow : public std::exception {
	virtual const char* what() const throw ();
};

#endif