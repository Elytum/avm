#ifndef MODULO_CPP
# define MODULO_CPP

#include <exception>

class Modulo : public std::exception {
	public:
		Modulo();
		~Modulo();
		Modulo(Modulo const & src);
		Modulo& operator=(Modulo const & rhs);
	private:
		virtual const char* what() const throw ();
};

#endif