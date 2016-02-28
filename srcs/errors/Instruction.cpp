#include <Instruction.hpp>
#include <string>

Instruction::Instruction(const int &id) : _id(id) {
}

Instruction::Instruction() : _id(0) {
}

Instruction::~Instruction() {
}

Instruction::Instruction(Instruction const & src) : _id(src._id) {
}

Instruction& Instruction::operator=(Instruction const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

const char *Instruction::what() const throw () { return ("Error : \033[1;31mIllegal Instruction "+std::to_string(_id)+"\033[0m").c_str(); }