#include "serverRoomNotFoundException.h"

RoomNotFoundException::RoomNotFoundException(std::string message)
		: runtime_error(message) {}
