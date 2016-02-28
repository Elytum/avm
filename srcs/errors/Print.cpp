#include <Print.hpp>

const char *Print::what() const throw () { return ("Error : \033[1;31mPrint\033[0m"); }