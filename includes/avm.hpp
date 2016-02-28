#ifndef AVM_HPP
# define AVM_HPP

#include <string>

#define AVM_EXTENSION "avm"
#define COMPILED_EXTENSION "compiled"

typedef bool(*compiler)(std::string &code, const std::string &function, const std::string &type, const std::string &parameter);

enum functions : unsigned char
{
   NOP = 0,
   PUSH = 1,
   POP = 2,
   DUMP = 3,
   ASSERT = 4,
   ADD = 5,
   SUB = 6,
   MUL = 7,
   DIV = 8,
   MOD = 9,
   PRINT = 10,
   EXIT = 11,
   MAX_FUNCTION
};

std::string		compile(const std::string &program);
std::string		extract(const std::string &program, const compiler &compilator);
bool			   execute(const std::string &code);
std::string    get_file_contents(const char *filename);
bool			   put_file_contents(const std::string &content, const std::string &path);
int			   last_edit(const std::string &file_path);

#endif
