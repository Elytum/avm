#include <AssertEmpty.hpp>

AssertEmpty::AssertEmpty() {

}

AssertEmpty::~AssertEmpty() {

}

AssertEmpty::AssertEmpty(AssertEmpty const & src) {

}

AssertEmpty::AssertEmpty& operator=(AssertEmpty const & rhs) {

}


const char * AssertEmpty::what() const throw ()
{
	return ("Error : \033[1;31mAssert on empty stack\033[0m");
}