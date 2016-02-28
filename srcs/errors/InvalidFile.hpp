#ifndef INVALIDFILE_HPP
#define INVALIDFILE_HPP

#include <exception>

class InvalidFile: public std::exception {
	public:
		InvalidFile();
		~InvalidFile();
		InvalidFile(InvalidFile const & src);
		InvalidFile& operator=(InvalidFile const & rhs);
	private:
		virtual const char* what() const throw ();
};


#endif