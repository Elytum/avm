#include <avm.hpp>
#include <lexertk.hpp>

#include <iostream>
#include <vector>


struct function_definition
{
   std::string function;
   std::string type;
   std::string body;
   std::vector<std::string> var_list;
   std::string var;

   void clear()
   {
      function    .clear();
      type        .clear();
      body        .clear();
      var_list    .clear();
      var         .clear();
   }
};

struct parse_function_definition_impl : public lexertk::parser_helper
{
   /*
      Structure: function <name> (v0,v1,...,vn) { expression }
   */

   bool  finish_line(std::string& func_def)
   {
      std::size_t body_begin = current_token().position;
      std::size_t body_end   = current_token().position - 1;

      std::size_t size = body_end - body_begin + 1;

      const std::size_t index = body_begin + size;

      if (index < func_def.size())
         func_def = func_def.substr(index,func_def.size() - index);
      else
         func_def = "";
      return (true);
   }

   bool process(std::string& func_def, function_definition& fd)
   {
      /*                    Initialize lexel                   */
      if (!init(func_def))
         return false;

      /*                  Search for function name             */
      if (!token_is_then_assign(token_t::e_symbol, fd.function))
         return false;

      /*    If function doesn't take arugument, accept it      */
      if (func_def[current_token().position - 1] == '\n')
         return (finish_line(func_def));

      /*          Else it has to take an argument              */
      if (!token_is_then_assign(token_t::e_symbol, fd.type))
         return false;

      /*               Surrounded by parentheses               */
      if (!token_is(token_t::e_lbracket))
         return false;

      /*                   Containing a value                  */
      if (!token_is_then_assign(token_t::e_number, fd.var))
            return false;

      /*                 With closd brackets                   */
      if (!token_is(token_t::e_rbracket))
         return false;

      /*       In that case, the line must be finised          */
      if (func_def[current_token().position - 1] == '\n')
         return (finish_line(func_def));
      return false;
   }
};

bool parse_function_definition(std::string& func_def, function_definition& fd)
{
   parse_function_definition_impl   parser;
   return parser.process(func_def, fd);
}

void  write_function(function_definition &fd)
{
   // printf("Line[%02d]\n", line_count);
   // printf("Function: %s\n"      , fd.function.c_str() );
   // printf("Type: %s\n"      , fd.type.c_str() );
   // printf("Var: (%s)\n"    , fd.var.c_str()    );
   // printf("-----------------------------\n\n");
   printf("%s %s(%s)\n", fd.function.c_str(), fd.type.c_str(), fd.var.c_str());
   fd.clear();
}

std::string compile(const std::string &program)
{
   function_definition     fd;
   std::string             residual = program;

   int line_count = 0;
   int new_line_pos;

   do
   {
      if (parse_function_definition(residual,fd))
         write_function(fd);
      else
      {

         /* Find newline character, and in case it doesn't exist, stop the interpretation */
         if ((new_line_pos = residual.find("\n")) == -1)
         {
            printf("Line %i : Error : [%s]\n", line_count, residual.c_str());
            break ;
         }

         printf("Line %i : Error : [%s]\n", line_count, residual.substr(0, new_line_pos).c_str());
         residual.erase(0, new_line_pos + 1);
         if (residual.empty())
            break ;
      }
      ++line_count;
   }
   while (!residual.empty());
   std::cout << "*********************" << std::endl;
   return ("This is the program\n");
}

#include <iostream>
#include <fstream>

bool  put_file_contents(const std::string &content, const std::string &path)
{
   std::ofstream myfile;

   myfile.open (path.c_str());
   myfile << content.c_str();
   myfile.close();
   return true;
}

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

      if (extension != "avm") {
         std::cerr << "Unknown format: " << extension;
         return (1);
      }
      const std::string    name = file_path.substr(0, extension_begin - 1);
      const std::string    out = name + ".compiled";

      try {
         const std::string content = get_file_contents(file_path.c_str());
         const std::string compiled = compile(content);

         if (!(put_file_contents(content, out)))
            std::cerr << "Couldn't save compiled file" << std::endl;
      }
      catch ( const std::exception& e ) {
          std::cerr << e.what() << std::endl;
          return (1);
      }
      //
   }
   
   
   // if (ac == 2)
   //    file_path = av[1];
   
   // try {
   //    const std::string content = get_file_contents(file_path);
   //    compile(content);
   // }
   // catch ( const std::exception& e ) {
   //     std::cerr << e.what() << std::endl;
   //     return (1);
   // }

   return 0;
}
