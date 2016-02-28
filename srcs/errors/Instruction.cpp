#include <Instruction.hpp>
#include <string>

Instruction::Instruction(const int &id) : _id(id) {
}

const char *Instruction::what() const throw () { return ("Error : \033[1;31mIllegal Instruction "+std::to_string(_id)+"\033[0m").c_str(); }