#include <utility>
#include <iostream>
#include <sstream>
#include <list>
#include <string>

#include "server_Room.h"
#include "server_SeatAlreadyBookedException.h"
#include "server_InvalidInputParamsException.h"

#define ROW_SEPARATOR '\n'
#define COLUMN_SEPARATOR '\t'
#define ASCII_A int('A')

std::string Room::validateType(std::string type) {
	std::list<std::string> valid_type{"2D", "3D", "4D"};

	if ((std::find(valid_type.begin(), valid_type.end(), type)) ==
		valid_type.end()) {
		throw InvalidInputParamsException("Invalid Room Type");
	} else {
		return type;
	}
}

char Room::getRowName(int row) const {
	return char(ASCII_A + row - 1);
}

int Room::getRowNumber(char row) const {
	return (int(row) - ASCII_A + 1);
}

char Room::getAvailabilitySign(bool result) const {
	return result ? 'O' : 'X';
}

Room::Room(std::string id, std::string room_type) :
	id(std::move(id)),
	type(validateType(std::move(room_type))) {}

Room::Room(const Room &other) : Room(
		other.id,
		other.type) {}

Room::Room(Room &&other) noexcept : Room(
		std::move(other.id),
		std::move(other.type)) {}

size_t const Room::hash() const {
	std::hash<std::string> hasher;
	return hasher(id);
}

const bool Room::operator<(const Room &r) const {
	return true;
}

bool Room::operator==(const Room &other) const {
	return ((id == other.id) && (type == other.type));
}

Room &Room::operator=(const Room &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Copy values and pointer
	this->id = other.id;
	this->type = other.type;

	return *this;
}

Room &Room::operator=(Room &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = std::move(other.id);
	this->type = std::move(other.type);

	return *this;
}

Room::operator std::string() const {
	return id;
}

bool Room::hasId(std::string id) const {
	return (this->id == id);
}

std::string Room::getSeats() const {
	std::ostringstream ss;
	int columns_quantity = getColumnsQuantity();
	int rows_quantity = getRowsQuantity();
	for (int i = 1; i <= columns_quantity; i++) {
		ss << COLUMN_SEPARATOR << i;
	}
	ss << ROW_SEPARATOR;
	for (int i = 1; i <= rows_quantity; i++) {
		ss << getRowName(i);
		for (int j = 1; j <= columns_quantity; j++) {
			ss << COLUMN_SEPARATOR
			   << getAvailabilitySign(isSeatAvailable(i, j));
		}
		ss << ROW_SEPARATOR;
	}
	return ss.str();
}

void Room::book(char row, int column) {
	int row_number = getRowNumber(row);
	int rows_quantity = getRowsQuantity();
	int columns_quantity = getColumnsQuantity();
	if ((row_number > rows_quantity) || (column > columns_quantity)) {
		throw std::runtime_error(
				"Row or column passed as quantity is out of range");
	}
	if (!isSeatAvailable(row_number, column)) {
		std::ostringstream ss;
		ss << "Seat for row " + std::to_string(row) + " and column " +
			  std::to_string(column) +
			  " was already occupied.";
		throw SeatAlreadyBookedException(ss.str());
	} else {
		bookSeat(row_number, column);
	}
}

