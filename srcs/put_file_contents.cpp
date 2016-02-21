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