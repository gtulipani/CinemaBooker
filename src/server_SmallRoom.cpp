#include "server_SmallRoom.h"

int SmallRoom::getColumnsQuantity() const {
	return SMALL_ROOM_COLUMNS_QUANTITY;
}

int SmallRoom::getRowsQuantity() const {
	return SMALL_ROOM_ROWS_QUANTITY;
}

bool SmallRoom::isSeatAvailable(int row, int column) const {
	return seats_matrix[row - 1][column - 1];
}

void SmallRoom::bookSeat(int row, int column) {
	seats_matrix[row - 1][column - 1] = false;
}

void SmallRoom::initializeSeats() {
	for (int i = 0; i < SMALL_ROOM_ROWS_QUANTITY; i++) {
		for (int j = 0; j < SMALL_ROOM_COLUMNS_QUANTITY; j++) {
			seats_matrix[i][j] = true;
		}
	}
}

SmallRoom::SmallRoom(std::string id_as_string, std::string room_type) :
		Room(std::move(id_as_string), std::move(room_type)) {
	initializeSeats();
}

SmallRoom::SmallRoom(const SmallRoom &other) : Room(other.id, other.type) {}

SmallRoom::SmallRoom(SmallRoom &&other) noexcept : Room(
		std::move(other.id),
		std::move(other.type)) {}

bool SmallRoom::operator==(const SmallRoom &other) const {
	return ((this->id == other.id) && (this->type == other.type));
}

SmallRoom &SmallRoom::operator=(const SmallRoom &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = other.id;
	this->type = other.type;
	this->seats_matrix = other.seats_matrix;

	return *this;
}

SmallRoom &SmallRoom::operator=(SmallRoom &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = std::move(other.id);
	this->type = std::move(other.type);
	this->seats_matrix = other.seats_matrix;

	return *this;
}
