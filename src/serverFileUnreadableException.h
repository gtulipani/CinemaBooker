#ifndef __FILEUNREADABLEEXCEPTION_H__
#define __FILEUNREADABLEEXCEPTION_H__

#include <stdexcept>

class FileUnreadableException : public std::runtime_error {
public:
	explicit FileUnreadableException();
};


#endif //__FILEUNREADABLEEXCEPTION_H__
