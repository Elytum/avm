#include <fstream>
#include <string>
#include <cerrno>
#include <Errors.hpp>

  #include <iostream>
std::string   get_file_contents(const char *filename)
{
  std::cout << "Opening: " << filename << std::endl;
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw InvalidFile();
}