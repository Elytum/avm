#ifndef PRINT_CPP
# define PRINT_CPP

#include <exception>

class Print : public std::exception {
	virtual const char* what() const throw ();
};

#endif