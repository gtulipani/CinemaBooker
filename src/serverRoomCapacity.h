#ifndef __ROOM_CAPACITY_H__
#define __ROOM_CAPACITY_H__

#include <string>
#include <array>

#define ROW_SEPARATOR '\n'
#define COLUMN_SEPARATOR '\t'

template <class T, int ROW, int COL>
using Matrix = std::array<std::array<T, COL>, ROW>;

class RoomCapacity {
protected:
	std::string capacity_name;
	int rows_quantity;
	int columns_quantity;

	char getRowName(int row) const;
	int getRowNumber(char row) const;
	char getAvailabilitySign(bool result) const;
public:
	RoomCapacity(std::string capacity_name, int rows_quantity, int columns_quantity);

	RoomCapacity(const RoomCapacity &other);

	RoomCapacity(RoomCapacity&& other) noexcept;

	virtual ~RoomCapacity() = default;

	RoomCapacity& operator=(const RoomCapacity &other);

	RoomCapacity& operator=(RoomCapacity&& other) noexcept;

	// Overloading equals operator
	bool operator==(const RoomCapacity &other) const;

	virtual std::string getSeats() const = 0;

	virtual void book(char row, int column) = 0;
};


#endif //__ROOM_CAPACITY_H__
