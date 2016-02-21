#include <avm.hpp>

#include <iostream>

int main(int ac, char **av)
{
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
      {
         try {
            return (execute(get_file_contents(file_path.c_str())));
         }
         catch ( const std::exception& e ) {
             std::cerr << e.what() << std::endl;
             return (1);
         }
      }
      else if (extension != AVM_EXTENSION) {
         std::cerr << "Unknown format: " << extension;
         return (1);
      }
      const std::string    name = file_path.substr(0, extension_begin - 1);
      const std::string    out = name + ".compiled";

      if (last_edit(out) < last_edit(file_path))
      {
         std::cout << "Recompiling" << std::endl;
         try {
            const std::string content = get_file_contents(file_path.c_str());
            const std::string compiled = compile(content);

            if (!(put_file_contents(content, out)))
               std::cerr << "Couldn't save compiled file" << std::endl;
            execute(content);
         }
         catch ( const std::exception& e ) {
             std::cerr << e.what() << std::endl;
             return (1);
         }
      }
      else
      {
         try {
            execute(get_file_contents(file_path.c_str()));
         }
         catch ( const std::exception& e ) {
             std::cerr << e.what() << std::endl;
             return (1);
         }
      }
   }
   else {
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
      execute(compile(content));
   }
   return 0;
}
