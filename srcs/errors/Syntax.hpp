#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <exception>
#include <string>

class Syntax: public std::exception {
	public:
		Syntax(const std::string &line);
		Syntax();
		~Syntax();
		Syntax(Syntax const & src);
		Syntax& operator=(Syntax const & rhs);
	private:
		const std::string	_line;
		virtual const char*	what() const throw ();
};


#endif