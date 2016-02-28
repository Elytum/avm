#ifndef LEXICALTYPE_HPP
#define LEXICALTYPE_HPP

#include <exception>
#include <string>

class LexicalType: public std::exception {
	public:
		LexicalType(const std::string &line);
	private:
		const std::string	_line;
		virtual const char*	what() const throw ();
};


#endif