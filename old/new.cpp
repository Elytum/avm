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
      printf("Position: %i\n", current_token().position);
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

void interprete(const std::string &program)
{
   function_definition     fd;
   std::string             residual = program;
   int                     line_count = 0;

   do
   {
      if (parse_function_definition(residual,fd))
      {
         printf("Function: %s\n"      , fd.function.c_str() );
         printf("Type: %s\n"      , fd.type.c_str() );
         printf("Var: (%s)\n"    , fd.var.c_str()    );
         printf("-----------------------------\n\n");

      }
      else
      {
         // printf("Line %i : Error : [%s]\n", line_count, residual.substr(0, residual.find("\n")).c_str());
         // residual.erase(0, residual.find("\n") + 1);
         // if (residual.empty())
            break ;
         // break;
      }
      fd.clear();
      ++line_count;
   }
   while (!residual.empty());

   if (!residual.empty())
   {
      printf("Residual: %s\n",residual.c_str());
   }

   std::cout << "*********************" << std::endl;
}

int main()
{
   const std::string program = "; -------------\n; sample.avm -\n; -------------\n\npush a int32(42)\npush a int32(33)\nadd\npush float(44.55)\nmul\npush double(42.42)\npush int32(42)\ndump\npop\nassert double(42.42)\nexit\n";
   // const std::string program = "push int32(42)\npush int32(33)\nadd\npush float(44.55)\nmul\npush double(42.42)\npush int32(42)\ndump\npop\nassert double(42.42)\nexit\n";

   interprete(program);
   return 0;
}
