#include <utility>
#include <iostream>

#include "serverRoom.h"
#include "serverRoomCapacityCreator.h"

Room::Room(std::string id, RoomType room_type, RoomCapacity* capacity) :
	id(std::move(id)),
	type(std::move(room_type)),
	capacity(capacity) {}

Room::Room(std::string id_as_string, std::string room_type,
		   std::string capacity)
		: Room(
	std::move(id_as_string),
	RoomType(std::move(room_type)),
	RoomCapacityCreator::factoryMethod(std::move(capacity))) {}

Room::Room(const Room &other) : Room(
		other.id,
		other.type,
		other.capacity) {}

Room::Room(Room &&other) noexcept : Room(
		std::move(other.id),
		std::move(other.type),
		other.capacity) {
	other.capacity = nullptr;
}

/*Room::~Room() {
	delete capacity;
}*/

size_t const Room::hash() const {
	std::hash<std::string> hasher;
	return hasher(id);
}

const bool Room::operator<(const Room &r) const {
	return true;
}

bool Room::operator==(const Room &other) const {
	return ((id == other.id) && (type == other.type) &&
			(*capacity == *other.capacity));
}

Room &Room::operator=(const Room &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Free existing capacity
	delete[] capacity;

	// Copy values and pointer
	this->id = other.id;
	this->type = other.type;
	(*this->capacity) = (*other.capacity);

	return *this;
}

Room &Room::operator=(Room &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Free existing capacity
	delete[] capacity;

	this->id = std::move(other.id);
	this->type = std::move(other.type);
	(*this->capacity) = std::move(*(other.capacity));

	return *this;
}

Room::operator std::string() const {
	return id;
}

bool Room::hasId(std::string id) const {
	return (this->id == id);
}

std::string Room::getSeats() const {
	return capacity->getSeats();
}

void Room::book(char row, int column) {
	capacity->book(row, column);
}
