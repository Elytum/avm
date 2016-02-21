#include <avm.hpp>
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

int				get_int(const std::string &parameter, const int &min, const int &max)
{
	long int	value;
	char		*pos;

	if (!parameter.compare(0, 2, "0b"))
		value = strtol(parameter.substr(2).c_str(), &pos, 2);
	else if (!parameter.compare(0, 2, "0x"))
		value = strtol(parameter.c_str(), &pos, 16);
	else if (!parameter.compare(0, 1, "0"))
		value = strtol(parameter.c_str(), &pos, 8);
	else
		value = strtol(parameter.c_str(), &pos, 10);
	return (value);
	(void)min;
	(void)max;
}

double				get_double(const std::string &parameter, const double &min, const double &max)
{
	double		value;
	char		*pos;

	if (!parameter.compare(0, 2, "0b"))
		value = strtol(parameter.substr(2).c_str(), &pos, 2);
	else if (!parameter.compare(0, 2, "0x"))
		value = strtol(parameter.c_str(), &pos, 16);
	else if (!parameter.compare(0, 1, "0"))
		value = strtol(parameter.c_str(), &pos, 8);
	else
		value = strtod(parameter.c_str(), &pos);
	return (value);
	(void)min;
	(void)max;
}

bool		add_arguments(std::string &code, const std::string &type, const std::string &parameter)
{
	char	*ptr;

	if (type.empty() || parameter.empty())
		return (false);
	switch (hash_rt(type.c_str()))
	{
		case hash("int8"):
		{
			char v = get_int(parameter, CHAR_MIN, CHAR_MAX);
			ptr = reinterpret_cast<char *>(&v);
			code.push_back(INT8);
			code.append(ptr, 1);
			break ;
		}
		case hash("short int"):
		{
			short int v = get_int(parameter, SHRT_MIN, SHRT_MAX);
			ptr = reinterpret_cast<char *>(&v);
			code.push_back(INT16);
			code.append(ptr, 2);
			break ;
		}
		case hash("int32"):
		{
			int v = get_int(parameter, INT_MIN, INT_MAX);
			ptr = reinterpret_cast<char *>(&v);
			code.push_back(INT32);
			code.append(ptr, 4);
			break ;
		}
		case hash("float"):
		{
			float v = get_double(parameter, FLT_MIN, FLT_MAX);
			std::cout << "V: " << v << std::endl;
			ptr = reinterpret_cast<char *>(&v);
			code.push_back(FLOAT);
			code.append(ptr, 4);
			break ;
		}
		case hash("double"):
		{
			double v = get_double(parameter, DBL_MIN, DBL_MAX);
			std::cout << "V: " << v << std::endl;
			ptr = reinterpret_cast<char *>(&v);
			code.push_back(DOUBLE);
			code.append(ptr, 8);
			break ;
		}
	}
	return (true);
}

bool	compilator(std::string &code, const std::string &function, const std::string &type, const std::string &parameter)
{
	switch (hash_rt(function.c_str()))
	{
		case hash("push"):
		{
			code.push_back(PUSH);
			add_arguments(code, type, parameter);
			break ;
		}
		case hash("pop"):
		{
			code.push_back(POP);
			break ;
		}
		case hash("dump"):
		{
			code.push_back(DUMP);
			break ;
		}
		case hash("assert"):
		{
			code.push_back(ASSERT);
			add_arguments(code, type, parameter);
			break ;
		}
		case hash("add"):
		{
			code.push_back(ADD);
			break ;
		}
		case hash("sub"):
		{
			code.push_back(SUB);
			break ;
		}
		case hash("mul"):
		{
			code.push_back(MUL);
			break ;
		}
		case hash("div"):
		{
			code.push_back(DIV);
			break ;
		}
		case hash("mod"):
		{
			code.push_back(MOD);
			break ;
		}
		case hash("print"):
		{
			code.push_back(PRINT);
			break ;
		}
		case hash("exit"):
		{
			code.push_back(EXIT);
			break ;
		}
	}
	return (true);
}

std::string compile(const std::string &program)
{
	return (extract(program, &compilator));
}