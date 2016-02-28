#include <Type.hpp>

Type::Type() {

}

Type::~Type() {

}

Type::Type(Type const & src) {

}

Type::Type& operator=(Type const & rhs) {

}

const char *Type::what() const throw () { return ("Error : \033[1;31mUnknown type\033[0m"); }