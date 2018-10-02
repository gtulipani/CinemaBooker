#include <sstream>

#include "serverMediumRoomCapacity.h"
#include "serverSeatAlreadyBookedException.h"

MediumRoomCapacity::MediumRoomCapacity(std::string capacity) :
		RoomCapacity(std::move(capacity), MEDIUM_ROWS_QUANTITY,
					 MEDIUM_COLUMNS_QUANTITY) {
	// Initialize seats_matrix
	for (size_t i = 0; i < rows_quantity; i++) {
		for (size_t j = 0; j < columns_quantity; j++)
			seats_matrix[i][j] = true;
	}
}

MediumRoomCapacity::MediumRoomCapacity(const MediumRoomCapacity &other)
		: RoomCapacity(
		other.capacity_name,
		other.rows_quantity,
		other.columns_quantity) {}

MediumRoomCapacity::MediumRoomCapacity(MediumRoomCapacity &&other) noexcept
		: RoomCapacity(
		std::move(other.capacity_name),
		other.rows_quantity,
		other.columns_quantity) {}

MediumRoomCapacity &
MediumRoomCapacity::operator=(const MediumRoomCapacity &other) {
	if (this == &other) {
		return *this; // other is myself!
	}
	this->seats_matrix = other.seats_matrix;

	return *this;
}

MediumRoomCapacity &
MediumRoomCapacity::operator=(MediumRoomCapacity &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->seats_matrix = other.seats_matrix;

	return *this;
}

std::string MediumRoomCapacity::getSeats() const {
	std::ostringstream ss;
	for (int i = 1; i <= columns_quantity; i++) {
		ss << COLUMN_SEPARATOR << i;
	}
	ss << ROW_SEPARATOR;
	for (int i = 1; i <= rows_quantity; i++) {
		ss << getRowName(i);
		for (int j = 1; j <= columns_quantity; j++) {
			ss << COLUMN_SEPARATOR
			   << getAvailabilitySign(seats_matrix[i - 1][j - 1]);
		}
		ss << ROW_SEPARATOR;
	}
	return ss.str();
}

void MediumRoomCapacity::book(char row, int column) {
	int row_number = getRowNumber(row);
	if ((row_number > rows_quantity) || (column > columns_quantity)) {
		throw std::runtime_error(
				"Row or column passed as quantity is out of range");
	}
	if (!seats_matrix[row_number - 1][column - 1]) {
		std::ostringstream ss;
		ss << "Seat for row " + std::to_string(row) + " and column " +
			  std::to_string(column) +
			  " was already occupied.";
		throw SeatAlreadyBookedException(ss.str());
	} else {
		seats_matrix[row_number - 1][column - 1] = false;
	}
}
