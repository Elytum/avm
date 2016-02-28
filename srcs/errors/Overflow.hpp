#ifndef OVERFLOW_CPP
# define OVERFLOW_CPP

#include <exception>
#include <string>

class Overflow: public std::exception {
	public:
		Overflow(const int &a);
		Overflow(const int &a, const int &b, const std::string &operation);
		Overflow();
		~Overflow();
		Overflow(Overflow const & src);
		Overflow& operator=(Overflow const & rhs);
	private:
		const int			_a;
		const int			_b;
		const std::string	_operation;
		virtual const char*	what() const throw ();
};

#endif