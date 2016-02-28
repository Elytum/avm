#ifndef WRONG_ASSERT_CPP
# define WRONG_ASSERT_CPP

#include <exception>

class WrongAssert : public std::exception {
	public:
		WrongAssert();
		~WrongAssert();
		WrongAssert(WrongAssert const & src);
		WrongAssert& operator=(WrongAssert const & rhs);
	private:
		virtual const char* what() const throw ();
};

#endif