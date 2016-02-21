#ifndef AVM_HPP
# define AVM_HPP

#include <string>

#define AVM_EXTENSION "avm"
#define COMPILED_EXTENSION "compiled"

typedef bool(*compiler)(std::string &code, const std::string &function, const std::string &type, const std::string &parameter);

enum functions : char
{
   PUSH,
   POP,
   DUMP,
   ASSERT,
   ADD,
   SUB,
   MUL,
   DIV,
   MOD,
   PRINT,
   EXIT
};

std::string		compile(const std::string &program);
std::string		extract(const std::string &program, const compiler &compilator);
bool			   execute(const std::string &code);
std::string    get_file_contents(const char *filename);
bool			   put_file_contents(const std::string &content, const std::string &path);
int			   last_edit(const std::string &file_path);

#endif
