#ifndef __INVALID_SHOWINGS_FILE_EXCEPTION_H__
#define __INVALID_SHOWINGS_FILE_EXCEPTION_H__

#include <string>
#include <stdexcept>

#include "server_InputFileException.h"

class ShowingsInputFileException : public InputFileException {
public:
	explicit ShowingsInputFileException(std::string message);
};

#endif //__INVALID_SHOWINGS_FILE_EXCEPTION_H__
