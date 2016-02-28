#include <avm.hpp>
#include <Errors.hpp>
#include <IOperand.hpp>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <climits>
#include <cfloat>


static constexpr unsigned long long basis = 14695981039346656037ULL; 
static constexpr unsigned long long prime = 1099511628211ULL;

// compile-time hash helper function
constexpr unsigned long long hashone(char c, const char* remain, unsigned long long value)
{ return c == 0 ? value : hashone(remain[0], remain + 1, (value ^ c) * prime);}
// compile-time hash
constexpr unsigned long long hash(const char* str) 
{ return hashone(str[0], str + 1, basis); }

// run-time hash
unsigned long long hash_rt(const char* str) 
{
    unsigned long long hash = basis;
    while (*str != 0) {
        hash ^= str[0];
        hash *= prime;
        ++str;
    }
    return hash;
}

bool		add_arguments(std::string &code, const std::string &type, const std::string &parameter)
{
	if (type.empty() || parameter.empty())
		return (false);
	switch (hash_rt(type.c_str()))
	{
		case hash("int8"):
		{
			code.push_back(INT8);
			break ;
		}
		case hash("int16"):
		{
			code.push_back(INT16);
			break ;
		}
		case hash("int32"):
		{
			code.push_back(INT32);
			break ;
		}
		case hash("float"):
		{
			code.push_back(FLOAT);
			break ;
		}
		case hash("double"):
		{
			code.push_back(DOUBLE);
			break ;
		}
		default:
		{
			throw LexicalType(type);
		}
	}
	code.append(parameter);
	code += '\0';
	return (true);
}

bool	compilator(std::string &code, const std::string &function, const std::string &type, const std::string &parameter)
{
	switch (hash_rt(function.c_str()))
	{
		case hash("nop"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(NOP);
			break ;
		}
		case hash("push"):
		{
			if (type.empty() || parameter.empty())
				throw MissingArgument(function);
			code.push_back(PUSH);
			add_arguments(code, type, parameter);
			break ;
		}
		case hash("pop"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(POP);
			break ;
		}
		case hash("dump"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(DUMP);
			break ;
		}
		case hash("assert"):
		{
			if (type.empty() || parameter.empty())
				throw MissingArgument(function);
			code.push_back(ASSERT);
			add_arguments(code, type, parameter);
			break ;
		}
		case hash("add"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(ADD);
			break ;
		}
		case hash("sub"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(SUB);
			break ;
		}
		case hash("mul"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(MUL);
			break ;
		}
		case hash("div"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(DIV);
			break ;
		}
		case hash("mod"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(MOD);
			break ;
		}
		case hash("print"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(PRINT);
			break ;
		}
		case hash("exit"):
		{
			if (!type.empty())
				throw ExtraArgument(function, type);
			code.push_back(EXIT);
			break ;
		}
		default:
		{
			throw LexicalFunction(function);
		}
	}
	return (true);
}

std::string compile(const std::string &program)
{
	return (extract(program, &compilator));
}