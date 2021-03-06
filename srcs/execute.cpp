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
	std::string						sa;
	std::string						sb;
	size_t							id = 1;

	types[INT8] = INT8;
	types[INT16] = INT16;
	types[INT32] = INT32;
	types[FLOAT] = FLOAT;
	types[DOUBLE] = DOUBLE;

	try
	{
		while (i < code.size())
		{
			switch (code[i * sizeof(functions)])
			{
				case NOP:
				{
					++i;
					break ;
				}
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
					if (stack.empty())
						throw Pop();
					stack.pop_back();
					break ;
				}
				case DUMP:
				{
					++i;
					for (std::vector<IOperand const *>::iterator it = stack.end() - 1; it >= stack.begin(); --it) {
						std::cout << (*it)->toString() << std::endl;
					}
					break ;
				}
				case ASSERT:
				{
					++i;
					if (stack.empty())
						throw AssertEmpty();
					if (static_cast<unsigned int>(code[i]) >= MAX_TYPE)
						throw Type();
					a = Factory::instance()->createOperand(types[(unsigned int)code[i]], code.substr(i + 1, code.size() - i - 1));
					sa = a->toString();
					sb = stack.back()->toString();
					if (sa != sb)
						throw WrongAssert();
					delete a;
					i += 1 + strlen(code.c_str() + i + 1) + 1;
					break ;
				}
				case ADD:
				{
					++i;
					if (stack.size() < 2)
						throw MathError("+");
					a = stack.back();
					stack.pop_back();
					b = stack.back();
					stack.pop_back();
					stack.push_back(*a + *b);
					delete a; delete b;
					break ;
				}
				case SUB:
				{
					++i;
					if (stack.size() < 2)
						throw MathError("-");
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
					if (stack.size() < 2)
						throw MathError("*");
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
					if (stack.size() < 2)
						throw MathError("/");
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
					if (stack.size() < 2)
						throw MathError("%");
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
					if (stack.empty())
						throw PrintEmpty();
					a = stack.back();
					if (a->getType() != INT8)
						throw Print();
					std::cout << static_cast<Int8 const *>(a)->getValue() << std::endl;
					break ;
				}
				case EXIT:
				{
					++i;
					return (true);
				}
				default:
					throw Instruction(code[i * sizeof(functions)]);
			}
			++id;
		}
	}
	catch ( const std::exception & e ) 
	{
		std::cerr << "Instruction " << id << " : " << e.what() << std::endl;
	}
	return (false);
}