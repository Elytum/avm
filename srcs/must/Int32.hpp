#ifndef INT32_HPP
# define INT32_HPP

# include <Operand.hpp>

class Int32: public Operand <int32_t>
{
	public:
		Int32(int32_t value);
};

#endif