#ifndef DIVISION_CPP
# define DIVISION_CPP

#include <exception>

class Division : public std::exception {
	public:
		Division();
		~Division();
		Division(Division const & src);
		Division& operator=(Division const & rhs);
	private:
		virtual const char* what() const throw ();
};

#endif