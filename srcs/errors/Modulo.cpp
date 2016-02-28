#include <Modulo.hpp>

Modulo::Modulo() {
}

Modulo::~Modulo() {
}

Modulo::Modulo(Modulo const & src) {

}

Modulo::Modulo& operator=(Modulo const & rhs) {

}

const char *Modulo::what() const throw () { return ("Error : \033[1;31mModulo\033[0m"); }