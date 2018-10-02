#include "serverInvalidRoomException.h"

InvalidRoomException::InvalidRoomException(std::string message)
		: runtime_error(message) {}
