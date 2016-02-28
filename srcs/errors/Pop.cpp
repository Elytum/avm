#include <Pop.hpp>

Pop::Pop() {
}

Pop::~Pop() {
}

Pop::Pop(Pop const & src) {
	
}

Pop::Pop& operator=(Pop const & rhs) {

}

const char *Pop::what() const throw () { return ("Error : \033[1;31mPop on empty stack\033[0m"); }