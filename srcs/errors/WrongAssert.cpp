#include <WrongAssert.hpp>

AssertEmpty::AssertEmpty() {

}

AssertEmpty::~AssertEmpty() {

}

AssertEmpty::AssertEmpty(AssertEmpty const & src) {

}

AssertEmpty::AssertEmpty& operator=(AssertEmpty const & rhs) {

}

const char *WrongAssert::what() const throw () { return ("Error : \033[1;31mWrongAssert\033[0m"); }