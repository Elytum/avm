#include <avm.hpp>
#include <iostream>

bool		execute(const std::string &code)
{
	size_t	i = 0;

	while (i < code.size())
	{
		switch (code[i * sizeof(functions)])
		{
			case PUSH:
			{
				std::cout << "PUSH" << std::endl;
				break ;
			}
			case POP:
			{
				std::cout << "POP" << std::endl;
				break ;
			}
			case DUMP:
			{
				std::cout << "DUMP" << std::endl;
				break ;
			}
			case ASSERT:
			{
				std::cout << "ASSERT" << std::endl;
				break ;
			}
			case ADD:
			{
				std::cout << "ADD" << std::endl;
				break ;
			}
			case SUB:
			{
				std::cout << "SUB" << std::endl;
				break ;
			}
			case MUL:
			{
				std::cout << "MUL" << std::endl;
				break ;
			}
			case DIV:
			{
				std::cout << "DIV" << std::endl;
				break ;
			}
			case MOD:
			{
				std::cout << "MOD" << std::endl;
				break ;
			}
			case PRINT:
			{
				std::cout << "PRINT" << std::endl;
				break ;
			}
			case EXIT:
			{
				std::cout << "EXIT" << std::endl;
				break ;
			}
		}
		++i;
	}
	// std::cout << "Executing [" << code << "]" << std::endl;
	// (void)code;
	return true;
}