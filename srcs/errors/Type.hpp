#ifndef TYPE_CPP
# define TYPE_CPP

#include <exception>

class Type : public std::exception {
	public:
		Type();
		~Type();
		Type(Type const & src);
		Type& operator=(Type const & rhs);
	private:
		virtual const char* what() const throw ();
};

#endif