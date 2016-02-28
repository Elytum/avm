#ifndef OPERAND_TPP
# define OPERAND_TPP

# include <Factory.hpp>		// createOperand
# include <sstream>			// std::ostringstream
# include <stdlib.h>		// atof
# include <math.h>			// fmod
# include <Errors.hpp>		// errors
# include <cfenv>			// std::except

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


template<typename T>
class	Operand : public IOperand
{

private:
	
	T							_value;
	eOperandType		const	_type;
	std::string					_str;
	
	Operand<T>( void );
	Operand<T>( Operand<T> const & src );
	Operand<T> & operator = ( Operand<T> const & rhs );

public:

	Operand<T>( T value, eOperandType type):_value(value), _type(type), _str(std::to_string(_value))
	{
		if (_str.find(".") != std::string::npos)
			_str.erase(_str.find_last_not_of('0') + 1, std::string::npos);
	}

	virtual ~Operand<T>()
	{

	}

	virtual int getPrecision( void ) const
	{
		return (_type);
	}
	
	virtual eOperandType getType( void ) const
	{
		return (_type);
	}

	virtual	T	getValue( void ) const
	{
		return (_value);
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const
	{
		eOperandType	type	= (getPrecision() < rhs.getPrecision()) ? rhs.getType() : _type;
		double			value;
		const IOperand	*ret;

		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = _value + atof(rhs.toString().c_str());
		if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow(_value, atof(rhs.toString().c_str()), "+");
		else if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow(_value, atof(rhs.toString().c_str()), "+");
		try {
			ret = Factory::instance()->createOperand(type, patch::to_string(value));
		}
		catch (const Overflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "+");
		}
		catch (const Underflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "+");
		}
		return (ret);
	}
	
	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType	type	= (getPrecision() < rhs.getPrecision()) ? rhs.getType() : _type;
		double			value;
		const IOperand	*ret;

		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = _value - atof(rhs.toString().c_str());
		if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow(_value, atof(rhs.toString().c_str()), "-");
		else if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow(_value, atof(rhs.toString().c_str()), "-");
		try {
			ret = Factory::instance()->createOperand(type, patch::to_string(value));
		}
		catch (const Overflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "-");
		}
		catch (const Underflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "-");
		}
		return (ret);
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType	type	= (getPrecision() < rhs.getPrecision()) ? rhs.getType() : _type;
		double			value;
		const IOperand	*ret;

		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = _value * atof(rhs.toString().c_str());
		if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow(_value, atof(rhs.toString().c_str()), "*");
		else if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow(_value, atof(rhs.toString().c_str()), "*");
		try {
			ret = Factory::instance()->createOperand(type, patch::to_string(value));
		}
		catch (const Overflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "*");
		}
		catch (const Underflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "*");
		}
		return (ret);
	}
	
	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		eOperandType	type	= (getPrecision() < rhs.getPrecision()) ? rhs.getType() : _type;
		double			value	= atof(rhs.toString().c_str());
		const IOperand	*ret;

		if (value == 0.0)
			throw Division();
		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = _value / value;
		if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow(_value, atof(rhs.toString().c_str()), "/");
		else if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow(_value, atof(rhs.toString().c_str()), "/");
		try {
			ret = Factory::instance()->createOperand(type, patch::to_string(value));
		}
		catch (const Overflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "/");
		}
		catch (const Underflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "/");
		}
		return (ret);
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const
	{
		eOperandType	type	= (getPrecision() < rhs.getPrecision()) ? rhs.getType() : _type;
		double			value	= atof(rhs.toString().c_str());
		const IOperand	*ret;

		if (value == 0.0)
			throw Division();
		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = fmod(_value, value);
		if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow(_value, atof(rhs.toString().c_str()), "%");
		else if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow(_value, atof(rhs.toString().c_str()), "%");
		try {
			ret = Factory::instance()->createOperand(type, patch::to_string(value));
		}
		catch (const Overflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "%");
		}
		catch (const Underflow& e) {
			throw Overflow(_value, atof(rhs.toString().c_str()), "%");
		}
		return (ret);
	}

	virtual std::string const & toString( void ) const
	{
		return (_str);
	}

};

template<typename T>
std::ostream &	operator << (std::ostream & o, Operand<T> const & op)
{
	o << op.toString();
	return (o);
}

#include <Int8.hpp>
#include <Int16.hpp>
#include <Int32.hpp>
#include <Float.hpp>
#include <Double.hpp>

#endif
