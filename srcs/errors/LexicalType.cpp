#include <LexicalType.hpp>

LexicalType::LexicalType(const std::string &line) : _line(line) {
}

const char * LexicalType::what() const throw ()
{
	return ("Error : Lexical error with type '"+_line+"'").c_str();
}