/*
 *****************************************************************
 *                 Simple C++ Lexer Toolkit Library              *
 *                                                               *
 * Lexer Examples                                                *
 * Author: Arash Partow (2001)                                   *
 * URL: http://www.partow.net/programming/lexer/index.html       *
 *                                                               *
 * Copyright notice:                                             *
 * Free use of the Simple C++ Lexer Toolkit Library is permitted *
 * under the guidelines and in accordance with the most current  *
 * version of the Common Public License.                         *
 * http://www.opensource.org/licenses/cpl1.0.php                 *
 *                                                               *
 *****************************************************************
*/


#include <avm.hpp>
 
#include <iostream>
#include <string>
#include <vector>

#include "lexertk.hpp"

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

void interprete(const std::string &program)
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
}

// #include <fstream>
// #include <string>
// #include <cerrno>

// std::string get_file_contents(const char *filename)
// {
//   std::ifstream in(filename, std::ios::in | std::ios::binary);
//   if (in)
//   {
//     std::string contents;
//     in.seekg(0, std::ios::end);
//     contents.resize(in.tellg());
//     in.seekg(0, std::ios::beg);
//     in.read(&contents[0], contents.size());
//     in.close();
//     return(contents);
//   }
//   throw(InvalidFile());
// }

int main(int ac, char **av)
{
   if (ac != 2)
   {
      std::cout << "Wrong format" << std::endl;
      return (1);
   }
   
   try {
      const std::string content = get_file_contents(av[1]);
      interprete(content);
   }
   catch ( const std::exception& e ) {
       std::cerr << e.what() << std::endl;
       return (1);
   }

   return 0;
}
