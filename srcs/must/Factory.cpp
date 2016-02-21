#include <Factory.hpp>
#include <Int8.hpp>
// #include "Int16.hpp"
// #include "Int32.hpp"
// #include "Float.hpp"
// #include "Double.hpp"
#include <iostream>
#include <string>

#include <stdexcept>
#include <climits>
#include <cfloat>
#include <cfenv>
#include <math.h>

static Factory* s_instance = nullptr;

Factory* Factory::instance(void)
{
	return s_instance;
}

Factory::Factory(void)
{
	if (!s_instance)
		s_instance = this;
	this->_v.push_back(&Factory::createInt8);
	// this->_v.push_back(&Factory::createInt16);
	// this->_v.push_back(&Factory::createInt32);
	// this->_v.push_back(&Factory::createFloat);
	// this->_v.push_back(&Factory::createDouble);
}

Factory::~Factory()
{
	std::cout << "Factory [DESTRUCTED]" << std::endl;
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
	return ((this->*(_v[type]))(value));
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	double	test;

	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	test = stod(value);
	// if (std::fetestexcept(FE_UNDERFLOW))
	// 	throw UnderflowError();
	// else if (std::fetestexcept(FE_OVERFLOW))
	// 	throw OverflowError();
	// else if (test < SCHAR_MIN)
	// 	throw UnderflowError();
	// else if (test > SCHAR_MAX)
	// 	throw OverflowError();
	return (new Int8(test));
}

// IOperand const * Factory::createInt16( std::string const & value ) const
// {
// 	double	test;

// 	std::feclearexcept(FE_OVERFLOW);
// 	std::feclearexcept(FE_UNDERFLOW);
// 	test = stod(value);
// 	if (std::fetestexcept(FE_UNDERFLOW))
// 		throw UnderflowError();
// 	if (std::fetestexcept(FE_OVERFLOW))
// 		throw OverflowError();
// 	if (test < SHRT_MIN)
// 		throw UnderflowError();
// 	else if (test > SHRT_MAX)
// 		throw OverflowError();
// 	return (new Int16(test));
// }

// IOperand const * Factory::createInt32( std::string const & value ) const
// {
// 	double	test;

// 	std::feclearexcept(FE_OVERFLOW);
// 	std::feclearexcept(FE_UNDERFLOW);
// 	test = stod(value);
// 	if (std::fetestexcept(FE_UNDERFLOW))
// 		throw UnderflowError();
// 	if (std::fetestexcept(FE_OVERFLOW))
// 		throw OverflowError();
// 	if (test < INT_MIN)
// 		throw UnderflowError();
// 	else if (test > INT_MAX)
// 		throw OverflowError();
// 	return (new Int32(test));
// }

// IOperand const * Factory::createFloat( std::string const & value ) const
// {
// 	double test;

// 	std::feclearexcept(FE_OVERFLOW);
//     std::feclearexcept(FE_UNDERFLOW);
// 	test = stod(value);
// 	if (std::fetestexcept(FE_UNDERFLOW))
// 		throw UnderflowError();
// 	if (std::fetestexcept(FE_OVERFLOW))
// 		throw OverflowError();
// 	if (test < FLT_MIN)
// 		throw UnderflowError();
// 	if (test > FLT_MAX)
// 		throw OverflowError();
// 	return (new Float(test));
// }

// IOperand const * Factory::createDouble( std::string const & value ) const
// {
// 	double	test;

// 	std::feclearexcept(FE_OVERFLOW);
//     std::feclearexcept(FE_UNDERFLOW);
// 	test = stod(value);
// 	if (std::fetestexcept(FE_UNDERFLOW))
// 		throw UnderflowError();
// 	if (std::fetestexcept(FE_OVERFLOW))
// 		throw OverflowError();
// 	return (ne