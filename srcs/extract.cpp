#include <lexertk.hpp>
#include <avm.hpp>

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
      int sign = 0;

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

      /*                  If we see have minus                 */
      if (token_is(token_t::e_sub))
      /*                        We save it                     */
         sign = -1;
      /*                Else if we see have minus              */
      else if (token_is(token_t::e_add))
      /*                        We save it                     */
         sign = 1;
      /*                   Containing a value                  */
      if (!token_is_then_assign(token_t::e_number, fd.var))
            return false;
      if (sign == 1)
         fd.var = "+" + fd.var;
      else if (sign == 1)
         fd.var = "-" + fd.var;

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

void  compile_function(std::string &code, function_definition &fd, const compiler &compilator)
{
   compilator(code, fd.function, fd.type, fd.var);
   fd.clear();
   return ;
}

std::string extract(const std::string &program, const compiler &compilator)
{
   function_definition     fd;
   std::string             residual = program;
   std::string             code;

   int line_count = 0;
   int new_line_pos;

   /*                    As long as there is lines to compile                       */
   do
   {
   /*                   If lexer parsing goes according to plan                     */
      if (parse_function_definition(residual,fd))
   /*                 Compile the function and add it to the code                   */
         compile_function(code, fd, compilator);
      else
   /*                           Else report the error                               */
      {
   /*                           Find newline character                              */
         if ((new_line_pos = residual.find("\n")) == -1)
         {
   /*          If there is not, report the error on the remaining line              */
            printf("Line %i : Error : [%s]\n", line_count, residual.c_str());
   /*                        Then stop the compilation                              */
            break ;
         }

   /*                      Else Report the error on only this line                  */
         printf("Line %i : Error : [%s]\n", line_count, residual.substr(0, new_line_pos).c_str());
   /*                               And erase this line                             */
         residual.erase(0, new_line_pos + 1);
   /*                         If there is nothing more to compile                   */
         if (residual.empty())
   /*                              Stop the compilation                             */
            break ;
      }
   /*                             Increment the line counter                        */
      ++line_count;
   }
   while (!residual.empty());
   /*                             Return the compiled code                          */
   return (code);
}