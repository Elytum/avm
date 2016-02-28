#include <Print.hpp>

Print::Print() {

}

Print::~Print() {

}

Print::Print(Print const & src) {

}

Print::Print& operator=(Print const & rhs) {

}

const char *Print::what() const throw () { return ("Error : \033[1;31mPrint\033[0m"); }