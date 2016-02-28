#ifndef SYNTAX_HPP
#define SYNTAX_HPP

#include <exception>
#include <string>

class Syntax: public std::exception {
	public:
		Syntax(const std::string &line);
	private:
		const std::string	_line;
		virtual const char*	what() const throw ();
};


#endif