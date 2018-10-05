#include "server_MediumRoom.h"

int MediumRoom::getColumnsQuantity() const {
	return MEDIUM_ROOM_COLUMNS_QUANTITY;
}

int MediumRoom::getRowsQuantity() const {
	return MEDIUM_ROOM_ROWS_QUANTITY;
}

bool MediumRoom::isSeatAvailable(int row, int column) const {
	return seats_matrix[row - 1][column - 1];
}

void MediumRoom::bookSeat(int row, int column) {
	seats_matrix[row - 1][column - 1] = false;
}

void MediumRoom::initializeSeats() {
	for (int i = 0; i < MEDIUM_ROOM_ROWS_QUANTITY; i++) {
		for (int j = 0; j < MEDIUM_ROOM_COLUMNS_QUANTITY; j++) {
			seats_matrix[i][j] = true;
		}
	}
}

MediumRoom::MediumRoom(std::string id_as_string, std::string room_type) :
		Room(std::move(id_as_string), std::move(room_type)) {
	initializeSeats();
}

MediumRoom::MediumRoom(const MediumRoom &other) : Room(other.id, other.type) {}

MediumRoom::MediumRoom(MediumRoom &&other) noexcept : Room(
		std::move(other.id),
		std::move(other.type)) {}

bool MediumRoom::operator==(const MediumRoom &other) const {
	return ((this->id == other.id) && (this->type == other.type));
}

MediumRoom &MediumRoom::operator=(const MediumRoom &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = other.id;
	this->type = other.type;
	this->seats_matrix = other.seats_matrix;

	return *this;
}

MediumRoom &MediumRoom::operator=(MediumRoom &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = std::move(other.id);
	this->type = std::move(other.type);
	this->seats_matrix = other.seats_matrix;

	return *this;
}

bool MediumRoom::hasSeatsAvailble() const {
	bool at_least_one_seat_available = false;
	int i = 0;
	while ((i < MEDIUM_ROOM_ROWS_QUANTITY) && (!at_least_one_seat_available)) {
		int j = 0;
		while ((j < MEDIUM_ROOM_COLUMNS_QUANTITY) && !at_least_one_seat_available) {
			at_least_one_seat_available = seats_matrix[i][j];
			j++;
		}
		i++;
	}
	return at_least_one_seat_available;
}
