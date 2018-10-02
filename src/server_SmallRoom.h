#ifndef __SERVER_SMALL_ROOM_H__
#define __SERVER_SMALL_ROOM_H__

#include <array>
#include "server_Room.h"

#define SMALL_ROOM_ROWS_QUANTITY 5
#define SMALL_ROOM_COLUMNS_QUANTITY 6

class SmallRoom : public Room {
private:
	Matrix<bool, SMALL_ROOM_ROWS_QUANTITY, SMALL_ROOM_COLUMNS_QUANTITY> seats_matrix;
protected:
	int getColumnsQuantity() const override;
	int getRowsQuantity() const override;
	bool isSeatAvailable(int row, int column) const override;
	void bookSeat(int row, int column) override;
	void initializeSeats() override;
public:
	SmallRoom(std::string id_as_string, std::string room_type);

	SmallRoom(const SmallRoom &other);

	SmallRoom(SmallRoom &&other) noexcept;

	~SmallRoom() override = default;

	// Overloading equals operator
	bool operator==(const SmallRoom &other) const;

	// Overloading the assignment by copy
	SmallRoom &operator=(const SmallRoom &other);

	// Overloading the assignment by movement
	SmallRoom &operator=(SmallRoom &&other) noexcept;
};


#endif //__SERVER_SMALL_ROOM_H__
