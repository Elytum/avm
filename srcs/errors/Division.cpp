#include <Division.hpp>

Division::Division() {

}

Division::~Division() {
}

Division::Division(Division const & src) {
	*this = src;
}

Division& Division::operator=(Division const & rhs) {
		if (this != &rhs)
		*this = rhs;
	return (*this);
}

const char *Division::what() const throw () { return ("Error : \033[1;31mDivision\033[0m"); }