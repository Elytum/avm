#ifndef TYPE_CPP
# define TYPE_CPP

#include <exception>

class Type : public std::exception {
	virtual const char* what() const throw ();
};

#endif