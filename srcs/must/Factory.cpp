#include <Operand.hpp>	// Every types
#include <Errors.hpp>	// errors
#include <cfenv>		// std::except
#include <climits>		// limit int8/16/32
#include <cfloat>		// limit float/double

double			get_double(const char *parameter)
{
	double		value;
	char		*pos;
	char		sign = 0;

	if (*parameter == '+' && parameter[1] >= '0' && parameter[1] <= '9')
		++parameter;
	else if (*parameter == '-' && parameter[1] >= '0' && parameter[1] <= '9')
	{
		sign = -1;
		++parameter;
	}
	else
		sign = 0;
	if (*parameter == '0')
	{
		if (parameter[1] == 'b')
			value = strtol(parameter + 2, &pos, 2);
		else if (parameter[1] == 'x')
			value = strtol(parameter + 2, &pos, 16);
		else
			value = strtol(parameter + 1, &pos, 8);
	}
	else
		value = strtod(parameter, &pos);
	if (sign == -1)
		return (-value);
	return (value);
}

static Factory* s_instance = nullptr;

Factory* Factory::instance(void)
{
	if (!s_instance)
		s_instance = new Factory;
	return s_instance;
}

Factory::Factory(void)
{
	if (!s_instance)
		s_instance = this;
	this->_v[INT8] = &Factory::createInt8;
	this->_v[INT16] = &Factory::createInt16;
	this->_v[INT32] = &Factory::createInt32;
	this->_v[FLOAT] = &Factory::createFloat;
	this->_v[DOUBLE] = &Factory::createDouble;
}

Factory::~Factory()
{
}

Factory::Factory(Factory const & src)
{
	*this = src;
}

Factory & 	Factory::operator = (Factory const & rhs)
{
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
	if (type >= MAX_TYPE)
		exit(0);
	return ((this->*(_v[type]))(value));
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	double	test;

	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	test = get_double(value.c_str());
	if (std::fetestexcept(FE_UNDERFLOW))
		throw Underflow(test);
	else if (std::fetestexcept(FE_OVERFLOW))
		throw Overflow(test);
	else if (test < SCHAR_MIN)
		throw Underflow(test);
	else if (test > SCHAR_MAX)
		throw Overflow(test);
	return (new Int8(test));
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
	double	test;

	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	test = get_double(value.c_str());
	if (std::fetestexcept(FE_UNDERFLOW))
		throw Underflow(test);
	if (std::fetestexcept(FE_OVERFLOW))
		throw Overflow(test);
	if (test < SHRT_MIN)
		throw Underflow(test);
	else if (test > SHRT_MAX)
		throw Overflow(test);
	return (new Int16(test));
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
	double	test;

	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	test = get_double(value.c_str());
	if (std::fetestexcept(FE_UNDERFLOW))
		throw Underflow(test);
	if (std::fetestexcept(FE_OVERFLOW))
		throw Overflow(test);
	if (test < INT_MIN)
		throw Underflow(test);
	else if (test > INT_MAX)
		throw Overflow(test);
	return (new Int32(test));
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
	double test;

	std::feclearexcept(FE_OVERFLOW);
    std::feclearexcept(FE_UNDERFLOW);
	test = get_double(value.c_str());
	if (std::fetestexcept(FE_UNDERFLOW))
		throw Underflow(test);
	if (std::fetestexcept(FE_OVERFLOW))
		throw Overflow(test);
	if (test < FLT_MIN)
		throw Underflow(test);
	if (test > FLT_MAX)
		throw Overflow(test);
	return (new Float(test));
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
	double	test;

	std::feclearexcept(FE_OVERFLOW);
    std::feclearexcept(FE_UNDERFLOW);
	test = get_double(value.c_str());
	if (std::fetestexcept(FE_UNDERFLOW))
		throw Underflow(test);
	if (std::fetestexcept(FE_OVERFLOW))
		throw Overflow(test);
	return (new Double(test));
}
