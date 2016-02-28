#include <Overflow.hpp>

Overflow::Overflow(const int &a) : _a(a), _b(0), _operation("") {
}

Overflow::Overflow(const int &a, const int &b, const std::string &operation) : _a(a), _b(b), _operation(operation) {
}

Overflow::Overflow() : _a(0), _b(0), _operation("") {
}

Overflow::~Overflow() {
}

Overflow::Overflow(Overflow const & src) : _a(src._a), _b(src._b), _operation(src._operation) {
}

Overflow& Overflow::operator=(Overflow const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

const char *Overflow::what() const throw () {
	if (_operation == "")
		return ("Error : \033[1;31mOverflow with "+std::to_string(_a)).c_str();
	else
		return ("Error : \033[1;31mOverflow\033[0m with \033[1;31m"+std::to_string(_a)+" "+_operation+" "+std::to_string(_b)+"\033[0m").c_str();

}