#ifndef AVM_HPP
# define AVM_HPP

#include <string>

#define AVM_EXTENSION "avm"
#define COMPILED_EXTENSION "compiled"

std::string		compile(const std::string &program);
bool			execute(const std::string &code);
std::string		get_file_contents(const char *filename);
bool			put_file_contents(const std::string &content, const std::string &path);
int				last_edit(const std::string &file_path);

#endif
