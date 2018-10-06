#include <string>

#include "server_RoomCreator.h"
#include "server_InvalidInputParamsException.h"

#define SMALL_ROOM_CAPACITY_IDENTIFIER "chica"
#define MEDIUM_ROOM_CAPACITY_IDENTIFIER "mediana"
#define LARGE_ROOM_CAPACITY_IDENTIFIER "grande"

SmallRoom *
RoomCreator::createSmallRoom(std::string id_as_string, std::string room_type) {
	return new SmallRoom(std::move(id_as_string), std::move(room_type));
}

MediumRoom *
RoomCreator::createMediumRoom(std::string id_as_string, std::string room_type) {
	return new MediumRoom(std::move(id_as_string), std::move(room_type));
}

LargeRoom *
RoomCreator::createLargeRoom(std::string id_as_string, std::string room_type) {
	return new LargeRoom(std::move(id_as_string), std::move(room_type));
}

Room *
RoomCreator::factoryMethod(std::string id_as_string, std::string room_type,
						   std::string capacity) {
	if (capacity == SMALL_ROOM_CAPACITY_IDENTIFIER) {
		return createSmallRoom(std::move(id_as_string), std::move(room_type));
	}
	if (capacity == MEDIUM_ROOM_CAPACITY_IDENTIFIER) {
		return createMediumRoom(std::move(id_as_string), std::move(room_type));
	}
	if (capacity == LARGE_ROOM_CAPACITY_IDENTIFIER) {
		return createLargeRoom(std::move(id_as_string), std::move(room_type));
	} else {
		throw InvalidInputParamsException("Invalid Room Capacity");
	}
}
