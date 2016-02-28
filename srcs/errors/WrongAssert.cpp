#include <WrongAssert.hpp>

const char *WrongAssert::what() const throw () { return ("Error : \033[1;31mWrongAssert\033[0m"); }