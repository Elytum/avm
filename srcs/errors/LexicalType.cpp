#include <LexicalType.hpp>

LexicalType::LexicalType(const std::string &line) : _line(line) {
}

const char * LexicalType::what() const throw ()
{
	return ("Error : \033[1;31mLexical\033[0m error with \033[1;31mtype\033[0m '\033[1;31m"+_line+"\033[0m'").c_str();
}