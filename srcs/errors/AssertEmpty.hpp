#ifndef ASSERTEMPTY_HPP
#define ASSERTEMPTY_HPP

#include <exception>
#include <string>

class AssertEmpty: public std::exception {
	public:
		AssertEmpty();
		~AssertEmpty();
		AssertEmpty(AssertEmpty const & src);
		AssertEmpty& operator=(AssertEmpty const & rhs);
	private:
		virtual const char*	what() const throw ();
};


#endif