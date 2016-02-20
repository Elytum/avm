#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <exception>

class SyntaxError: public std::exception {
	virtual const char* what() const throw ();
};


#endif