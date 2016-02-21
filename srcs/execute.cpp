#include <iostream>

bool  execute(const std::string &code)
{
   std::cout << "Executing [" << code << "]" << std::endl;
   (void)code;
   return true;
}