#include "server_LargeRoom.h"

int LargeRoom::getColumnsQuantity() const {
	return LARGE_ROOM_COLUMNS_QUANTITY;
}

int LargeRoom::getRowsQuantity() const {
	return LARGE_ROOM_ROWS_QUANTITY;
}

bool LargeRoom::isSeatAvailable(int row, int column) const {
	return seats_matrix[row - 1][column - 1];
}

void LargeRoom::bookSeat(int row, int column) {
	seats_matrix[row - 1][column - 1] = false;
}

void LargeRoom::initializeSeats() {
	for (int i = 0; i < LARGE_ROOM_ROWS_QUANTITY; i++) {
		for (int j = 0; j < LARGE_ROOM_COLUMNS_QUANTITY; j++) {
			seats_matrix[i][j] = true;
		}
	}
}

LargeRoom::LargeRoom(std::string id_as_string, std::string room_type) :
		Room(std::move(id_as_string), std::move(room_type)) {
	initializeSeats();
}

LargeRoom::LargeRoom(const LargeRoom &other) : Room(other.id, other.type) {}

LargeRoom::LargeRoom(LargeRoom &&other) noexcept : Room(
		std::move(other.id),
		std::move(other.type)) {}

bool LargeRoom::operator==(const LargeRoom &other) const {
	return ((this->id == other.id) && (this->type == other.type));
}

LargeRoom &LargeRoom::operator=(const LargeRoom &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = other.id;
	this->type = other.type;
	this->seats_matrix = other.seats_matrix;

	return *this;
}

LargeRoom &LargeRoom::operator=(LargeRoom &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = std::move(other.id);
	this->type = std::move(other.type);
	this->seats_matrix = other.seats_matrix;

	return *this;
}
