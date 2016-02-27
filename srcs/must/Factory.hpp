#ifndef FACTORY_HPP
# define FACTORY_HPP

# include <IOperand.hpp>

class Factory;

typedef IOperand const * (Factory::*create)(std::string const &)const;

class Factory
{
	public:
		Factory();
		~Factory();
		Factory(Factory const & src);
		Factory& operator=(Factory const & rhs);
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;

		static Factory* instance();

	private:
		create	_v[5];
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
	};

#endif