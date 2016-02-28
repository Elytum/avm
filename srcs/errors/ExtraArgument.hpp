#ifndef EXTRAARGUMENT_HPP
#define EXTRAARGUMENT_HPP

#include <exception>
#include <string>

class ExtraArgument: public std::exception {
	public:
		ExtraArgument(const std::string &funct, const std::string &arg);
		ExtraArgument();
		~ExtraArgument();
		ExtraArgument(ExtraArgument const & src);
		ExtraArgument& operator=(ExtraArgument const & rhs);
	private:
		const std::string	_funct;
		const std::string	_arg;
		virtual const char*	what() const throw ();
};


#endif