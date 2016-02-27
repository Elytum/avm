#ifndef MODULO_CPP
# define MODULO_CPP

#include <exception>

class Modulo : public std::exception {
	virtual const char* what() const throw ();
};

#endif