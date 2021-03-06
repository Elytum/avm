#include <Syntax.hpp>

Syntax::Syntax(const std::string &line) : _line(line) {
}

Syntax::Syntax() : _line("") {
}

Syntax::~Syntax() {
}

Syntax::Syntax(Syntax const & src) : _line(src._line) {
}

Syntax& Syntax::operator=(Syntax const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

const char * Syntax::what() const throw ()
{
	return ("Error : \033[1;31mSyntax\033[0m error with \033[1;31mline\033[0m '\033[1;31m"+_line+"\033[0m'").c_str();
}