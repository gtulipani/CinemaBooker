#ifndef __ROOM_H__
#define __ROOM_H__

#include <string>

#include "serverRoomType.h"
#include "serverRoomCapacity.h"

class Room {
private:
	std::string id;
	RoomType type;
	RoomCapacity* capacity;
public:
	Room(std::string id, RoomType room_type, RoomCapacity* capacity);

	Room(std::string id_as_string, std::string room_type, std::string capacity);

	Room(const Room &other);

	Room(Room &&other) noexcept;

	//~Room();

	// Define hash function in order to work with std:unordered_set
	size_t const hash() const;

	// Override less operator in order to work with std::set
	const bool operator<(const Room &r) const;

	// Overloading equals operator
	bool operator==(const Room &other) const;

	// Overloading the assignment by copy
	Room &operator=(const Room &other);

	// Overloading the assignment by movement
	Room &operator=(Room &&other) noexcept;

	// Overloading the std::string casting to obtain the title
	explicit operator std::string() const;

	bool hasId(std::string id) const;

	std::string getSeats() const;

	void book(char row, int column);
};


#endif //__ROOM_H__
