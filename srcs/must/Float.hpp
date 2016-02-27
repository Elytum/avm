#ifndef FLOAT_HPP
# define FLOAT_HPP

# include <Operand.hpp>

class Float: public Operand <float>
{
	public:
		Float(float value);
};

#endif