#include <string>

#include "server_ClientOperationException.h"

ClientOperationException::ClientOperationException(std::string message)
		: runtime_error(message) {}
