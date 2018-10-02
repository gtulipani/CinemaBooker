#include "serverMovieShowingNotFoundException.h"

MovieShowingNotFoundException::MovieShowingNotFoundException(std::string message)
		: runtime_error(message) {}
