#include <avm.hpp>
#include <iostream>

bool		get_value(const std::string &code, size_t &i, char &type, int &value)
{
	const std::string ptr = code.substr(i + 1);

	type = code[i++];
	if (type == INT8)
	{
		value = *reinterpret_cast<const char *>(ptr.c_str());
		++i;
	}
	else if (type == INT16)
	{
		value = *reinterpret_cast<const short int *>(ptr.c_str());
		i += 2;
	}
	else if (type == INT32)
	{
		value = *reinterpret_cast<const int *>(ptr.c_str());
		i += 4;
	}
	else
		return (false);
	return (true);
}

bool		execute(const std::string &code)
{
	size_t	i = 0;
	char	type;
	int		value;

	while (i < code.size())
	{
		switch (code[i * sizeof(functions)])
		{
			case PUSH:
			{
				++i;
				get_value(code, i, type, value);

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