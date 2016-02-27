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
	std::string			const	_str;
	
	Operand<T>( void );
	Operand<T>( Operand<T> const & src );
	Operand<T> & operator = ( Operand<T> const & rhs );

public:

	Operand<T>( T value, eOperandType type):_value(value), _type(type), _str(std::to_string(_value))
	{
	}

	virtual ~Operand<T>()
	{

	}

	virtual int getPrecision( void ) const
	{
		return (this->_type);
	}
	
	virtual eOperandType getType( void ) const
	{
		return (this->_type);
	}

	virtual	T	getValue( void ) const
	{
		return (this->_value);
	}

	virtual IOperand const * operator+( IOperand const & rhs ) const
	{
		eOperandType type = (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		double			value;

		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = this->_value + atof(rhs.toString().c_str());
		if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow();
		else if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow();
		return Factory::instance()->createOperand(type, patch::to_string(value));
	}
	
	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType	type = (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		double			value;

		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = this->_value - atof(rhs.toString().c_str());
		if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow();
		else if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow();
		return Factory::instance()->createOperand(type, patch::to_string(value));
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType	type	= (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		double			value;
		
		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = this->_value * atof(rhs.toString().c_str());
		if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow();
		else if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow();
		return Factory::instance()->createOperand(type, patch::to_string(value));
	}
	
	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		eOperandType	type	= (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		double			value	= atof(rhs.toString().c_str());

		if (value == 0)
			throw Division();
		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = this->_value / value;
		if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow();
		else if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow();
		return Factory::instance()->createOperand(type, patch::to_string(value));
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const
	{
		eOperandType	type	= (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		double			value	= atof(rhs.toString().c_str());

		if (value == 0)
			throw Division();
		std::feclearexcept(FE_OVERFLOW);
		std::feclearexcept(FE_UNDERFLOW);
		value = fmod(this->_value, value);
		if (std::fetestexcept(FE_UNDERFLOW))
			throw Underflow();
		else if (std::fetestexcept(FE_OVERFLOW))
			throw Overflow();
		return Factory::instance()->createOperand(type, patch::to_string(value));
	}

	virtual std::string const & toString( void ) const
	{
		return (this->_str);
	}

};

template<typename T>
std::ostream & 	operator << (std::ostream & o, Operand<T> const & op)
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
