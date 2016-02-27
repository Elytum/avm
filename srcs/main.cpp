#include <avm.hpp>
#include <iostream>

std::string    handle_stdin(void)
{
   std::string    content;
   int            pos;

   for (std::string line; std::getline(std::cin, line);) {
      if ((pos = line.find(";;")) != -1)
      {
         content += line.substr(0, pos) + '\n';
         break ;
      }
      content += line + '\n';
   }
   return (compile(content));
}

std::string    handle_code(const std::string &file_path)
{
   const std::string    name = file_path.substr(0, file_path.rfind("."));
   const std::string    out = name + ".compiled";

   if (1 == 1 || last_edit(out) < last_edit(file_path))
   {
      try {
         const std::string content = get_file_contents(file_path.c_str());
         const std::string compiled = compile(content);

         if (!(put_file_contents(compiled, out)))
            std::cerr << "Couldn't save compiled file" << std::endl;
         return (compiled);
      }
      catch ( const std::exception& e ) {
         std::cerr << e.what() << std::endl;
         std::string empty;
         return (empty);
      }
   }
   else
   {
      try {
         return (get_file_contents(out.c_str()));
      }
      catch ( const std::exception& e ) {
         std::cerr << e.what() << std::endl;
         std::string empty;
         return (empty);
      }
   }
}

std::string    handle_compiled(const std::string &file_path)
{
   try {
      return (get_file_contents(file_path.c_str()));
   }
   catch ( const std::exception& e ) {
      std::cerr << e.what() << std::endl;
      std::string empty;
      return (empty);
   }
}

int main(int ac, char **av)
{
   std::string    content;

   if (ac > 2)
   {
      std::cerr << "Wrong format: " << av[0] << " <FILE_PATH>" << std::endl;
      return (1);
   }
   else if (ac == 2) {
      const std::string    file_path = av[1];
      const int            extension_begin = file_path.rfind(".") + 1;
      const std::string    extension = file_path.substr(extension_begin, file_path.size() - extension_begin);

      if (extension == COMPILED_EXTENSION)
         content = handle_compiled(file_path);
      else if (extension == AVM_EXTENSION)
         content = handle_code(file_path);
      else
      {
         std::cerr << "Unknown format: " << extension;
         return (1);
      }
   }
   else
      content = handle_stdin();
   if (content.empty())
      return (1);
   execute(content);
   return 0;
}
