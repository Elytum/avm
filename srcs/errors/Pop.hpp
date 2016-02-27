#ifndef POP_CPP
# define POP_CPP

#include <exception>

class Pop : public std::exception {
	virtual const char* what() const throw ();
};

#endif