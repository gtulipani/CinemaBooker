#ifndef __SERVER_MEDIUM_ROOM_H__
#define __SERVER_MEDIUM_ROOM_H__

#include <array>
#include "server_Room.h"

#define MEDIUM_ROOM_ROWS_QUANTITY 10
#define MEDIUM_ROOM_COLUMNS_QUANTITY 11

class MediumRoom : public Room {
private:
	Matrix<bool, MEDIUM_ROOM_ROWS_QUANTITY, MEDIUM_ROOM_COLUMNS_QUANTITY> seats_matrix;
protected:
	int getColumnsQuantity() const override;
	int getRowsQuantity() const override;
	bool isSeatAvailable(int row, int column) const override;
	void bookSeat(int row, int column) override;
	void initializeSeats() override;
public:
	MediumRoom(std::string id_as_string, std::string room_type);

	MediumRoom(const MediumRoom &other);

	MediumRoom(MediumRoom &&other) noexcept;

	~MediumRoom() override = default;

	// Overloading equals operator
	bool operator==(const MediumRoom &other) const;

	// Overloading the assignment by copy
	MediumRoom &operator=(const MediumRoom &other);

	// Overloading the assignment by movement
	MediumRoom &operator=(MediumRoom &&other) noexcept;
};


#endif //__SERVER_MEDIUM_ROOM_H__
