#include <Int8.hpp>
#include <iostream>
Int8::Int8(int8_t value): Operand <int8_t> (value, INT8) {
	std::cout << "Int8: " << (int)value << std::endl;
}