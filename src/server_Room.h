#ifndef __ROOM_H__
#define __ROOM_H__

#include <string>
#include <array>

template<class T, int ROW, int COL>
using Matrix = std::array<std::array<T, COL>, ROW>;

class Room {
private:
	char getRowName(int row) const;

	int getRowNumber(char row) const;

	char getAvailabilitySign(bool result) const;

	std::string validateType(std::string type);

protected:
	std::string id;
	std::string type;

	virtual int getColumnsQuantity() const = 0;

	virtual int getRowsQuantity() const = 0;

	virtual bool isSeatAvailable(int row, int column) const = 0;

	virtual void bookSeat(int row, int column) = 0;

	virtual void initializeSeats() = 0;

public:
	Room(std::string id_as_string, std::string room_type);

	Room(const Room &other);

	Room(Room &&other) noexcept;

	virtual ~Room() = default;

	// Define hash function in order to work with std:unordered_set
	size_t const hash() const;

	// Override less operator in order to work with std::set
	const bool operator<(const Room &r) const;

	// Overloading equals operator
	bool operator==(const Room &other) const;

	// Overloading the assignment by copy
	Room &operator=(const Room &other);

	// Overloading the assignment by movement
	Room &operator=(Room &&other) noexcept;

	// Overloading the std::string casting to obtain the title
	explicit operator std::string() const;

	bool hasId(std::string id) const;

	std::string getSeats() const;

	void book(char row, int column, std::ostringstream &stream);

	virtual bool hasSeatsAvailble() const = 0;
};


#endif //__ROOM_H__
