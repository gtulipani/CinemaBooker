#ifndef __ROOM_NOT_FOUND_EXCEPTION_H__
#define __ROOM_NOT_FOUND_EXCEPTION_H__

#include <stdexcept>
#include <string>

class RoomNotFoundException : public std::runtime_error {
public:
	explicit RoomNotFoundException(std::string message);
};


#endif //__ROOM_NOT_FOUND_EXCEPTION_H__
