#ifndef INT8_CLASS_HPP
# define INT8_CLASS_HPP

# include <Operand.hpp>

class Int8: public Operand<int8_t>
{
	public:
		Int8(int8_t value);
};

#endif