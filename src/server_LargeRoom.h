#ifndef __SERVER_LARGE_ROOM_H__
#define __SERVER_LARGE_ROOM_H__

#include <array>
#include "server_Room.h"

#define LARGE_ROOM_ROWS_QUANTITY 15
#define LARGE_ROOM_COLUMNS_QUANTITY 16

class LargeRoom : public Room {
private:
	Matrix<bool, LARGE_ROOM_ROWS_QUANTITY, LARGE_ROOM_COLUMNS_QUANTITY> seats_matrix;
protected:
	int getColumnsQuantity() const override;
	int getRowsQuantity() const override;
	bool isSeatAvailable(int row, int column) const override;
	void bookSeat(int row, int column) override;
	void initializeSeats() override;
public:
	LargeRoom(std::string id_as_string, std::string room_type);

	LargeRoom(const LargeRoom &other);

	LargeRoom(LargeRoom &&other) noexcept;

	~LargeRoom() override = default;

	// Overloading equals operator
	bool operator==(const LargeRoom &other) const;

	// Overloading the assignment by copy
	LargeRoom &operator=(const LargeRoom &other);

	// Overloading the assignment by movement
	LargeRoom &operator=(LargeRoom &&other) noexcept;
};

#endif //__SERVER_LARGE_ROOM_H__
