#ifndef LEXICALFUNCTION_HPP
#define LEXICALFUNCTION_HPP

#include <exception>
#include <string>

class LexicalFunction: public std::exception {
	public:
		LexicalFunction(const std::string &line);
		LexicalFunction();
		~LexicalFunction();
		LexicalFunction(LexicalFunction const & src);
		LexicalFunction& operator=(LexicalFunction const & rhs);
	private:
		const std::string	_line;
		virtual const char*	what() const throw ();
};


#endif