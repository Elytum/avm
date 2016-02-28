#include <Type.hpp>

const char *Type::what() const throw () { return ("Error : \033[1;31mUnknown type\033[0m"); }