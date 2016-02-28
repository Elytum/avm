#ifndef POP_CPP
# define POP_CPP

#include <exception>

class Pop : public std::exception {
	public:
		Pop();
		~Pop();
		Pop(Pop const & src);
		Pop& operator=(Pop const & rhs);
	private:
		virtual const char* what() const throw ();
};

#endif