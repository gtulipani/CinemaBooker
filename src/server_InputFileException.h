#ifndef __FILEUNREADABLEEXCEPTION_H__
#define __FILEUNREADABLEEXCEPTION_H__

#include <stdexcept>

class InputFileException : public std::runtime_error {
public:
	explicit InputFileException();
};


#endif //__FILEUNREADABLEEXCEPTION_H__
