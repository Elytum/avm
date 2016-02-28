#include <lexertk.hpp>
#include <avm.hpp>
#include <Errors.hpp>

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

   void  finish_line(std::string& func_def)
   {
      std::size_t body_begin = current_token().position;
      std::size_t body_end   = current_token().position - 1;

      std::size_t size = body_end - body_begin + 1;

      const std::size_t index = body_begin + size;

      if (index < func_def.size())
         func_def = func_def.substr(index, func_def.size() - index);
      else
         func_def = "";
   }

   void  finish_error(std::string& func_def)
   {
      const std::size_t index = func_def.find("\n");
      std::string error;

      if (index == std::string::npos)
         error = func_def;
      else
         error = func_def.substr(0, index - 1);

      if (index < func_def.size())
         func_def = func_def.substr(index + 1,func_def.size() - index - 1);
      else
         func_def = "";
      throw Syntax(error);
   }

   void process(std::string &func_def, function_definition &fd)
   {
      int sign = 0;

      /*                    Initialize lexer                   */
      if (!init(func_def))
         finish_error(func_def);

      /*                  Search for function name             */
      if (!token_is_then_assign(token_t::e_symbol, fd.function))
         finish_error(func_def);

      /*    If function doesn't take argument, accept it       */
      if (func_def[current_token().position - 1] == '\n')
         { finish_line(func_def); return; }
      /*          Else it has to take an argument              */
      if (!token_is_then_assign(token_t::e_symbol, fd.type))
         finish_error(func_def);

      /*               Surrounded by parentheses               */
      if (!token_is(token_t::e_lbracket))
         finish_error(func_def);

      /*                  If we see have minus                 */
      if (token_is(token_t::e_sub))
      /*                        We save it                     */
         sign = -1;
      /*                Else if we see have plus               */
      else if (token_is(token_t::e_add))
      /*                        We save it                     */
         sign = 1;
      /*                   Containing a value                  */
      if (!token_is_then_assign(token_t::e_number, fd.var))
         finish_error(func_def);
      if (sign == 1)
         fd.var = "+" + fd.var;
      else if (sign == -1)
         fd.var = "-" + fd.var;

      /*                 With closed brackets                  */
      if (!token_is(token_t::e_rbracket))
         finish_error(func_def);

      /*       In that case, the line must be finised          */
      if (func_def[current_token().position - 1] == '\n')
         { finish_line(func_def); return; }
      finish_line(func_def); throw Syntax("lol");
   }
};

void  parse_function_definition(std::string &func_def, function_definition &fd)
{
   parse_function_definition_impl   parser;
   parser.process(func_def, fd);
}

void  compile_function(std::string &code, function_definition &fd, const compiler &compilator)
{
   compilator(code, fd.function, fd.type, fd.var);
}

int   countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0)
      return 0;
    int count = 0;

    for (size_t offset = str.find(sub); offset != std::string::npos; offset = str.find(sub, offset + sub.length()))
        ++count;
    return count;
}

size_t  get_line(const std::string &original, const std::string &residual)
{
   if (residual.empty())
      return (countSubstring(original, "\n") + (original.at(original.length() - 1) != '\n'));

   const size_t      pos = original.find(residual);
   const std::string passedCode = (pos != std::string::npos) ? original.substr(0, pos) : original;

   return (countSubstring(passedCode, "\n"));
}

std::string extract(const std::string &program, const compiler &compilator)
{
   function_definition     fd;
   std::string             residual = program;
   std::string             code;
   bool                    valid = true;

   /*                    As long as there is lines to compile                       */
   do
   {
   /*                   If lexer parsing goes according to plan                     */
      try {
         parse_function_definition(residual,fd);
   /*                 Compile the function and add it to the code                   */
         try {
            compile_function(code, fd, compilator);
         }
   /*                       If there is a compilation error                         */
         catch ( const std::exception& e ) {
   /*                       Rembember that the file is invalid                      */
            valid = false;
   /*                               And tell the error                              */
            std::cerr << "Line " << get_line(program, residual) << " : " << e.what() << std::endl;
         }
   /*                          If there is a lexer error                            */
      }
      catch ( const std::exception& e ) {
   /*                       Rembember that the file is invalid                      */
         valid = false;
   /*                               And tell the error                              */
         std::cerr << "Line " << get_line(program, residual) << " : " << e.what() << std::endl;
      }
      fd.clear();
   }
   while (!residual.empty());
   if (valid == false)
      exit(1);
   /*                             Return the compiled code                          */
   return (code);
}
