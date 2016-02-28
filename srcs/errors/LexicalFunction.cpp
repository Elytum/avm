#include <LexicalFunction.hpp>

LexicalFunction::LexicalFunction(const std::string &line) : _line(line) {
}

const char * LexicalFunction::what() const throw ()
{
	return ("Error : Lexical error with function '"+_line+"'").c_str();
}