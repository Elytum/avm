#ifndef INSTRUCTON_CPP
# define INSTRUCTON_CPP

#include <exception>

class Instruction : public std::exception {
	public:
		Instruction(const int &id);
	private:
		int					_id;
		virtual const char*	what() const throw ();
};

#endif