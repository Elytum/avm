#include <LexicalFunction.hpp>

LexicalFunction::LexicalFunction(const std::string &line) : _line(line) {
}

const char * LexicalFunction::what() const throw ()
{
	return ("Error : \033[1;31mLexical\033[0m error with \033[1;31mfunction\033[0m '\033[1;31m"+_line+"\033[0m'").c_str();
}