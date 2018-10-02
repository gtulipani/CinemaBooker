#ifndef __MEDIUM_ROOM_CAPACITY_H__
#define __MEDIUM_ROOM_CAPACITY_H__

#include "serverRoomCapacity.h"

#define MEDIUM_ROWS_QUANTITY 10
#define MEDIUM_COLUMNS_QUANTITY 11

class MediumRoomCapacity : public RoomCapacity {
private:
	Matrix<bool, MEDIUM_ROWS_QUANTITY, MEDIUM_COLUMNS_QUANTITY> seats_matrix;
public:
	explicit MediumRoomCapacity(std::string capacity);

	MediumRoomCapacity(const MediumRoomCapacity &other);

	MediumRoomCapacity(MediumRoomCapacity&& other) noexcept;

	~MediumRoomCapacity() override = default;

	// Overloading the assignment by copy
	MediumRoomCapacity& operator=(const MediumRoomCapacity &other);

	// Overloading the assignment by movement
	MediumRoomCapacity& operator=(MediumRoomCapacity&& other) noexcept;

	std::string getSeats() const override;

	void book(char row, int column) override;
};


#endif //__MEDIUM_ROOM_CAPACITY_H__
