#include <ExtraArgument.hpp>

ExtraArgument::ExtraArgument(const std::string &funct, const std::string &arg) : _funct(funct), _arg(arg) {
}

ExtraArgument::ExtraArgument() : _funct(""), _arg("") {
}

ExtraArgument::~ExtraArgument() {

}

ExtraArgument::ExtraArgument(ExtraArgument const & src) {

}

ExtraArgument::ExtraArgument& operator=(ExtraArgument const & rhs) {

}

const char * ExtraArgument::what() const throw ()
{
	return ("Error : \033[1;31mExtra argument \033[0m'\033[1;31m"+_arg+"\033[0m' error with \033[1;31mfunction\033[0m '\033[1;31m"+_funct+"\033[0m'").c_str();
}