#ifndef LEXICALFUNCTION_HPP
#define LEXICALFUNCTION_HPP

#include <exception>
#include <string>

class LexicalFunction: public std::exception {
	public:
		LexicalFunction(const std::string &line);
	private:
		const std::string	_line;
		virtual const char*	what() const throw ();
};


#endif