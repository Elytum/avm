#ifndef MATHERROR_HPP
#define MATHERROR_HPP

#include <exception>
#include <string>

class MathError: public std::exception {
	public:
		MathError(const std::string &operation);
		MathError();
		~MathError();
		MathError(MathError const & src);
		MathError& operator=(MathError const & rhs);
	private:
		const std::string	_operation;
		virtual const char*	what() const throw ();
};


#endif