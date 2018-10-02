#include "serverRoomCapacityCreator.h"
#include "serverInvalidRoomException.h"

#define SMALL_ROOM_CAPACITY_IDENTIFIER "chica"
#define MEDIUM_ROOM_CAPACITY_IDENTIFIER "mediana"
#define LARGE_ROOM_CAPACITY_IDENTIFIER "grande"

SmallRoomCapacity *
RoomCapacityCreator::createSmallRoomCapacity(std::string capacity) {
	return new SmallRoomCapacity(std::move(capacity));
}

MediumRoomCapacity *
RoomCapacityCreator::createMediumRoomCapacity(std::string capacity) {
	return new MediumRoomCapacity(std::move(capacity));
}

LargeRoomCapacity *
RoomCapacityCreator::createLargeRoomCapacity(std::string capacity) {
	return new LargeRoomCapacity(std::move(capacity));
}

RoomCapacity *RoomCapacityCreator::factoryMethod(std::string capacity) {
	if (capacity == SMALL_ROOM_CAPACITY_IDENTIFIER) {
		return createSmallRoomCapacity(std::move(capacity));
	}
	if (capacity == MEDIUM_ROOM_CAPACITY_IDENTIFIER) {
		return createMediumRoomCapacity(std::move(capacity));
	}
	if (capacity == LARGE_ROOM_CAPACITY_IDENTIFIER) {
		return createLargeRoomCapacity(std::move(capacity));
	} else {
		throw InvalidRoomException("Invalid Room Capacity");
	}
}
