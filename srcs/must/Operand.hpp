#ifndef OPERAND_TPP
# define OPERAND_TPP
# include "IOperand.hpp"
# include "Factory.hpp"
//# include "DivisionError.class.hpp"
# include <iostream>
# include <sstream>
# include <typeinfo>
# include <math.h>

#include <string>
#include <sstream>
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
	
	Operand<T>( T value, eOperandType type):_value(value), _type(type), _str(patch::to_string(_value))
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
		return Factory::instance()->createOperand(type, patch::to_string(static_cast<const double>(this->_value) + std::stod(rhs.toString())));
	}
	
	virtual IOperand const * operator-( IOperand const & rhs ) const
	{
		eOperandType type = (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		return Factory::instance()->createOperand(type, patch::to_string(this->_value - stod(rhs.toString())));
	}

	virtual IOperand const * operator*( IOperand const & rhs ) const
	{
		eOperandType type = (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		return Factory::instance()->createOperand(type, patch::to_string(this->_value * stod(rhs.toString())));
	}
	
	virtual IOperand const * operator/( IOperand const & rhs ) const
	{
		eOperandType 	type 	= (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		double 			nb2		= stod(rhs.toString());

		// if (nb2 == 0)
		// 	throw DivisionError();
		return Factory::instance()->createOperand(type, patch::to_string(this->_value / nb2));
	}

	virtual IOperand const * operator%( IOperand const & rhs ) const
	{
		std::string 	result;
		eOperandType 	type 	= (this->getPrecision() < rhs.getPrecision()) ? rhs.getType() : this->_type;
		double 			nb2		= stod(rhs.toString());

		if (nb2 == 0)
			throw DivisionError();
		result = patch::to_string(fmod(this->_value, nb2));

		return Factory::instance()->createOperand(type, result);
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

#endif
