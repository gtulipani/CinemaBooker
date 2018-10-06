#include <string>

#include "server_InvalidInputParamsException.h"

InvalidInputParamsException::InvalidInputParamsException(std::string message)
		: runtime_error(message) {}
