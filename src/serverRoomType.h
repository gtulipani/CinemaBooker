#ifndef __ROOM_TYPE_H__
#define __ROOM_TYPE_H__

#include <string>

class RoomType {
private:
	std::string type;

	void validateRoomType();
public:
	explicit RoomType(std::string type);

	std::string getRoomType() {
		return this->type;
	}

	// Overloading equals operator
	bool operator==(const RoomType &other) const;

	RoomType(const RoomType &other);

	RoomType(RoomType&& other) noexcept;

	RoomType& operator=(const RoomType &other);

	RoomType& operator=(RoomType&& other) noexcept;
};


#endif //__ROOM_TYPE_H__
