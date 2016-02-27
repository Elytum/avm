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
#include <vector>

#include <Int8.hpp>

bool			execute(const std::string &code)
{
	size_t							i = 0;
	eOperandType					types[5];
	std::vector<IOperand const *>	stack;
	IOperand const *				a;
	IOperand const *				b;

	(void)stack;
	types[INT8] = INT8;
	types[INT16] = INT16;
	types[INT32] = INT32;
	types[FLOAT] = FLOAT;
	types[DOUBLE] = DOUBLE;

	std::cout << "\tEXECUTING" << std::endl;
	while (i < code.size())
	{
		switch (code[i * sizeof(functions)])
		{
			case PUSH:
			{
				++i;
				if (static_cast<unsigned int>(code[i]) >= MAX_TYPE)
					exit (0);
				stack.push_back(Factory::instance()->createOperand(types[(unsigned int)code[i]], code.substr(i + 1, code.size() - i - 1)));
				i += 1 + strlen(code.c_str() + i + 1) + 1;
				break ;
			}
			case POP:
			{
				++i;
				break ;
			}
			case DUMP:
			{
				++i;
				break ;
			}
			case ASSERT:
			{
				++i;
				if (static_cast<unsigned int>(code[i]) >= MAX_TYPE)
					exit (0);
				a = Factory::instance()->createOperand(types[(unsigned int)code[i]], code.substr(i + 1, code.size() - i - 1));
				// if ()
				i += 1 + strlen(code.c_str() + i + 1) + 1;
				break ;
			}
			case ADD:
			{
				++i;
				a = stack.back();
				stack.pop_back();
				b = stack.back();
				stack.pop_back();
				std::cout << "'" << a->toString() << "' +'"  << b->toString() << "'"  << std::endl;
				stack.push_back(*a + *b);
				delete a; delete b;
				break ;
			}
			case SUB:
			{
				++i;
				a = stack.back();
				stack.pop_back();
				b = stack.back();
				stack.pop_back();
				stack.push_back(*a - *b);
				delete a; delete b;
				break ;
			}
			case MUL:
			{
				++i;
				a = stack.back();
				stack.pop_back();
				b = stack.back();
				stack.pop_back();
				stack.push_back(*a * *b);
				delete a; delete b;
				break ;
			}
			case DIV:
			{
				++i;
				a = stack.back();
				stack.pop_back();
				b = stack.back();
				stack.pop_back();
				stack.push_back(*a / *b);
				delete a; delete b;
				break ;
			}
			case MOD:
			{
				++i;
				a = stack.back();
				stack.pop_back();
				b = stack.back();
				stack.pop_back();
				stack.push_back(*a % *b);
				delete a; delete b;
				break ;
			}
			case PRINT:
			{
				++i;
				a = stack.back();
				if (a->getType() != INT8)
				{
					std::cerr << "ERROR NOT INT8" << std::endl;
					exit(1);
				}
				double value = static_cast<Int8 const *>(a)->getValue();
				std::cout << value << std::endl;
				break ;
			}
			case EXIT:
			{
				++i;
				break ;
			}
			default:
			{
				std::cerr << "Abort, illegal instruction" << std::endl;
				return (false);
			}
		}
	}
	return true;
}