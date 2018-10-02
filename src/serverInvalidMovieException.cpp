#include "serverInvalidMovieException.h"

InvalidMovieException::InvalidMovieException(std::string message)
		: runtime_error(message) {}
