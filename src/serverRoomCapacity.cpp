#include <utility>
#include <list>
#include <iostream>

#include "serverRoomCapacity.h"
#include "serverInvalidRoomException.h"

#define ASCII_A int('A')

char RoomCapacity::getRowName(int row) const {
	return char(ASCII_A + row - 1);
}

int RoomCapacity::getRowNumber(char row) const {
	return (int(row) - ASCII_A + 1);
}

char RoomCapacity::getAvailabilitySign(bool result) const {
	return result ? 'O' : 'X';
}

RoomCapacity::RoomCapacity(std::string capacity_name, int rows_quantity,
						   int columns_quantity) :
		capacity_name(std::move(capacity_name)),
		rows_quantity(rows_quantity),
		columns_quantity(columns_quantity) {}

bool RoomCapacity::operator==(const RoomCapacity &other) const {
	return ((capacity_name == other.capacity_name) &&
			(rows_quantity == other.rows_quantity) &&
			(columns_quantity == other.columns_quantity));
}

RoomCapacity::RoomCapacity(const RoomCapacity &other) : RoomCapacity(
		other.capacity_name,
		other.rows_quantity,
		other.columns_quantity) {}

RoomCapacity::RoomCapacity(RoomCapacity &&other) noexcept : RoomCapacity(
		std::move(other.capacity_name),
		other.rows_quantity,
		other.columns_quantity) {}

RoomCapacity &RoomCapacity::operator=(const RoomCapacity &other) {
	if (this == &other) {
		return *this; // other is myself!
	}
	this->capacity_name = other.capacity_name;
	this->rows_quantity = other.rows_quantity;
	this->columns_quantity = other.columns_quantity;

	return *this;
}

RoomCapacity &RoomCapacity::operator=(RoomCapacity &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->capacity_name = std::move(other.capacity_name);
	this->rows_quantity = other.rows_quantity;
	this->columns_quantity = other.columns_quantity;

	return *this;
}
