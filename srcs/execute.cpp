#include <avm.hpp>
#include <iostream>
#include <string.h>


#include <avm.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <climits>
#include <cfloat>

#include <IOperand.hpp>
#include <Factory.hpp>

double				get_double(const char *parameter, size_t &i, const double &min, const double &max)
{
	double		value;
	char		*pos;
	char		sign;

	if (*parameter == '+' && parameter[1] >= '0' && parameter[1] <= '9')
	{
		sign = 1;
		++parameter;
	}
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
	i += strlen(parameter) + (sign != 0) + 1;
	if (sign == -1)
		return (-value);
	return (value);
	(void)min;
	(void)max;
}

bool		get_value(const std::string &code, size_t &i, char &type, double &value)
{
	double		min = 0;
	double		max = 0;

	type = code[i++];
	if (type == INT8)
		value = get_double(code.c_str() + i, i, min, max);
	else if (type == INT16)
		value = get_double(code.c_str() + i, i, min, max);
	else if (type == INT32)
		value = get_double(code.c_str() + i, i, min, max);
	else if (type == FLOAT)
		value = get_double(code.c_str() + i, i, min, max);
	else if (type == DOUBLE)
		value = get_double(code.c_str() + i, i, min, max);
	else
		return (false);
	return (true);
}

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

bool			execute(const std::string &code)
{
	size_t		i = 0;
	char		type;
	double		value;

	while (i < code.size())
	{
		switch (code[i * sizeof(functions)])
		{
			case PUSH:
			{
				++i;
				get_value(code, i, type, value);
				Factory::instance()->createOperand(INT8, patch::to_string(value));

				std::cout << "PUSH " << value << std::endl;
				break ;
			}
			case POP:
			{
				++i;
				std::cout << "POP" << std::endl;
				break ;
			}
			case DUMP:
			{
				++i;
				std::cout << "DUMP" << std::endl;
				break ;
			}
			case ASSERT:
			{
				++i;
				get_value(code, i, type, value);

				std::cout << "ASSERT " << value << std::endl;
				break ;
			}
			case ADD:
			{
				++i;
				std::cout << "ADD" << std::endl;
				break ;
			}
			case SUB:
			{
				++i;
				std::cout << "SUB" << std::endl;
				break ;
			}
			case MUL:
			{
				++i;
				std::cout << "MUL" << std::endl;
				break ;
			}
			case DIV:
			{
				++i;
				std::cout << "DIV" << std::endl;
				break ;
			}
			case MOD:
			{
				++i;
				std::cout << "MOD" << std::endl;
				break ;
			}
			case PRINT:
			{
				++i;
				std::cout << "PRINT" << std::endl;
				break ;
			}
			case EXIT:
			{
				++i;
				std::cout << "EXIT" << std::endl;
				break ;
			}
			default:
			{
				std::cerr << "Abort, unknown instruction" << std::endl;
				return (false);
			}
		}
	}
	return true;
}