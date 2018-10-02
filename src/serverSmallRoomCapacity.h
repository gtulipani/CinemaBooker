#ifndef __SMALL_ROOM_CAPACITY_H__
#define __SMALL_ROOM_CAPACITY_H__

#include "serverRoomCapacity.h"

#define SMALL_ROWS_QUANTITY 5
#define SMALL_COLUMNS_QUANTITY 6

class SmallRoomCapacity : public RoomCapacity {
private:
	Matrix<bool, SMALL_ROWS_QUANTITY, SMALL_COLUMNS_QUANTITY> seats_matrix;
public:
	explicit SmallRoomCapacity(std::string capacity);

	SmallRoomCapacity(const SmallRoomCapacity &other);

	SmallRoomCapacity(SmallRoomCapacity&& other) noexcept;

	~SmallRoomCapacity() override = default;

	// Overloading the assignment by copy
	SmallRoomCapacity& operator=(const SmallRoomCapacity &other);

	// Overloading the assignment by movement
	SmallRoomCapacity& operator=(SmallRoomCapacity&& other) noexcept;

	std::string getSeats() const override;

	void book(char row, int column) override;
};


#endif //__SMALL_ROOM_CAPACITY_H__
