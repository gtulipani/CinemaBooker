#ifndef __FILEUNREADABLEEXCEPTION_H__
#define __FILEUNREADABLEEXCEPTION_H__

#include <string>
#include <stdexcept>

class InputFileException : public std::runtime_error {
public:
	explicit InputFileException(std::string file_path);
};


#endif //__FILEUNREADABLEEXCEPTION_H__
