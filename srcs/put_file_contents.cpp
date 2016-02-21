#include <iostream>
#include <fstream>

bool  put_file_contents(const std::string &content, const std::string &path)
{
	FILE *fd;

	if ((fd = fopen(path.c_str(), "wb")) == NULL)
		return false;
	fwrite(content.c_str(), 1, content.size(), fd);
	fclose(fd);
	return true;
}