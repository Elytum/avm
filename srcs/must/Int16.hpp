#ifndef INT16_HPP
# define INT16_HPP

# include <Operand.hpp>

class Int16: public Operand <int16_t>
{
	public:
		Int16(int16_t value);
};

#endif