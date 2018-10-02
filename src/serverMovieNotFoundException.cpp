#include "serverMovieNotFoundException.h"

MovieNotFoundException::MovieNotFoundException(std::string message)
		: runtime_error(message) {}
