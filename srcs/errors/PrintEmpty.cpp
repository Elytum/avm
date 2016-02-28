#include <PrintEmpty.hpp>

PrintEmpty::PrintEmpty() {

}

PrintEmpty::~PrintEmpty() {

}

PrintEmpty::PrintEmpty(PrintEmpty const & src) {

}

PrintEmpty::PrintEmpty& operator=(PrintEmpty const & rhs) {

}

const char * PrintEmpty::what() const throw ()
{
	return ("Error : \033[1;31mPrint on empty stack\033[0m");
}