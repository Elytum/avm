#ifndef PRINT_CPP
# define PRINT_CPP

#include <exception>

class Print : public std::exception {
	public:
		Print();
		~Print();
		Print(Print const & src);
		Print& operator=(Print const & rhs);
	private:
		virtual const char* what() const throw ();
};

#endif