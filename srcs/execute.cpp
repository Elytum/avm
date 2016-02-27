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
	size_t							line = 1;

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
					if (!stack.size())
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
					if (static_cast<unsigned int>(code[i]) >= MAX_TYPE)
						throw Type();
					a = Factory::instance()->createOperand(types[(unsigned int)code[i]], code.substr(i + 1, code.size() - i - 1));
					sa = a->toString();
					sb = stack.back()->toString();
					sa.erase(sa.find_last_not_of('0') + 1, std::string::npos);
					sb.erase(sb.find_last_not_of('0') + 1, std::string::npos);
					if (sa != sb)
						throw WrongAssert();
					delete a;
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
					throw Instruction();
			}
			++line;
		}
	}
	catch ( const std::exception & e ) 
	{
		std::cerr << "Line " << line << " : " << e.what() << std::endl;
	}
	return (false);
}