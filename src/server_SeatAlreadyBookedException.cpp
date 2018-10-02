#include "server_SeatAlreadyBookedException.h"

SeatAlreadyBookedException::SeatAlreadyBookedException(std::string message)
		: runtime_error(message) {}
