#include <MissingArgument.hpp>

MissingArgument::MissingArgument(const std::string &funct) : _funct(funct) {
}

MissingArgument::MissingArgument() : _funct("") {
}

MissingArgument::~MissingArgument() {
}

MissingArgument::MissingArgument(MissingArgument const & src) {

}

MissingArgument::MissingArgument& operator=(MissingArgument const & rhs) {

}

const char * MissingArgument::what() const throw ()
{
	return ("Error : \033[1;31mMissing argument\033[0m error with \033[1;31mline\033[0m '\033[1;31m"+_funct+"\033[0m'").c_str();
}