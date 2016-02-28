#ifndef PRINTEMPTY_HPP
#define PRINTEMPTY_HPP

#include <exception>
#include <string>

class PrintEmpty: public std::exception {
	public:
		PrintEmpty();
		~PrintEmpty();
		PrintEmpty(PrintEmpty const & src);
		PrintEmpty& operator=(PrintEmpty const & rhs);
	private:
		virtual const char*	what() const throw ();
};


#endif