#include <MathError.hpp>

MathError::MathError(const std::string &operation) : _operation(operation) {
}

MathError::MathError() : _operation("") {
}

MathError::~MathError() {
}

MathError::MathError(MathError const & src) : _operation(src._operation) {
}

MathError& MathError::operator=(MathError const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

const char * MathError::what() const throw ()
{
	return ("Error : \033[1;31mStack too little\033[0m for operation '\033[1;31m"+_operation+"\033[0m'").c_str();
}