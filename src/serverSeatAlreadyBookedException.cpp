#include "serverSeatAlreadyBookedException.h"

SeatAlreadyBookedException::SeatAlreadyBookedException(std::string message)
		: runtime_error(message) {}
