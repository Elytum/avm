#ifndef INSTRUCTON_CPP
# define INSTRUCTON_CPP

#include <exception>

class Instruction : public std::exception {
	public:
		Instruction(const int &id);
		Instruction();
		~Instruction();
		Instruction(Instruction const & src);
		Instruction& operator=(Instruction const & rhs);
	private:
		int					_id;
		virtual const char*	what() const throw ();
};

#endif