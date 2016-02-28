#include <LexicalType.hpp>

LexicalType::LexicalType(const std::string &line) : _line(line) {
}

LexicalType::LexicalType() : _line("") {
}

LexicalType::~LexicalType() {
}

LexicalType::LexicalType(LexicalType const & src) : _line(src._line) {
}

LexicalType& LexicalType::operator=(LexicalType const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

const char * LexicalType::what() const throw ()
{
	return ("Error : \033[1;31mLexical\033[0m error with \033[1;31mtype\033[0m '\033[1;31m"+_line+"\033[0m'").c_str();
}