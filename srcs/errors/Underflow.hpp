#ifndef UNDERFLOW_CPP
# define UNDERFLOW_CPP

#include <exception>
#include <string>

class Underflow: public std::exception {
	public:
		Underflow(const int &a);
		Underflow(const int &a, const int &b, const std::string &operation);
		Underflow();
		~Underflow();
		Underflow(Underflow const & src);
		Underflow& operator=(Underflow const & rhs);
	private:
		const int			_a;
		const int			_b;
		const std::string	_operation;
		virtual const char*	what() const throw ();
};

#endif