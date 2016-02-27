#ifndef AVM_HPP
# define AVM_HPP

#include <string>

#define AVM_EXTENSION "avm"
#define COMPILED_EXTENSION "compiled"

typedef bool(*compiler)(std::string &code, const std::string &function, const std::string &type, const std::string &parameter);

enum functions : unsigned char
{
   PUSH = 0,
   POP = 1,
   DUMP = 2,
   ASSERT = 3,
   ADD = 4,
   SUB = 5,
   MUL = 6,
   DIV = 7,
   MOD = 8,
   PRINT = 9,
   EXIT = 10,
   MAX_FUNCTION
};

std::string		compile(const std::string &program);
std::string		extract(const std::string &program, const compiler &compilator);
bool			   execute(const std::string &code);
std::string    get_file_contents(const char *filename);
bool			   put_file_contents(const std::string &content, const std::string &path);
int			   last_edit(const std::string &file_path);

#endif
