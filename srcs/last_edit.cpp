#include <sys/stat.h>
#include <string>

int		last_edit(const std::string &file_path)
{
   struct stat attrib;

   stat(file_path.c_str(), &attrib);
   return (attrib.st_mtime);
}