#ifndef INSTRUCTON_CPP
# define INSTRUCTON_CPP

#include <exception>

class Instruction : public std::exception {
	virtual const char* what() const throw ();
};

#endif