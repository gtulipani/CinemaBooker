#ifndef __INVALID_ROOM_EXCEPTION_H__
#define __INVALID_ROOM_EXCEPTION_H__

#include <stdexcept>
#include <string>

class InvalidRoomException : public std::runtime_error {
public:
	explicit InvalidRoomException(std::string message);
};


#endif //__INVALID_ROOM_EXCEPTION_H__
