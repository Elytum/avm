#ifndef MISSINGARGUMENT_HPP
#define MISSINGARGUMENT_HPP

#include <exception>
#include <string>

class MissingArgument: public std::exception {
	public:
		MissingArgument(const std::string &funct);
		MissingArgument();
		~MissingArgument();
		MissingArgument(MissingArgument const & src);
		MissingArgument& operator=(MissingArgument const & rhs);
	private:
		const std::string	_funct;
		virtual const char*	what() const throw ();
};


#endif