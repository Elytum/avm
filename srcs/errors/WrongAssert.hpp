#ifndef WRONG_ASSERT_CPP
# define WRONG_ASSERT_CPP

#include <exception>

class WrongAssert : public std::exception {
	virtual const char* what() const throw ();
};

#endif