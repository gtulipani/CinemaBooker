#ifndef __LARGE_ROOM_CAPACITY_H__
#define __LARGE_ROOM_CAPACITY_H__

#include "serverRoomCapacity.h"

#define LARGE_ROWS_QUANTITY 15
#define LARGE_COLUMNS_QUANTITY 16

class LargeRoomCapacity : public RoomCapacity {
private:
	Matrix<bool, LARGE_ROWS_QUANTITY, LARGE_COLUMNS_QUANTITY> seats_matrix;
public:
	explicit LargeRoomCapacity(std::string capacity);

	LargeRoomCapacity(const LargeRoomCapacity &other);

	LargeRoomCapacity(LargeRoomCapacity&& other) noexcept;

	~LargeRoomCapacity() override = default;

	// Overloading the assignment by copy
	LargeRoomCapacity& operator=(const LargeRoomCapacity &other);

	// Overloading the assignment by movement
	LargeRoomCapacity& operator=(LargeRoomCapacity&& other) noexcept;

	std::string getSeats() const override;

	void book(char row, int column) override;
};


#endif //__LARGE_ROOM_CAPACITY_H__
