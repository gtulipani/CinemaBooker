#ifndef __MOVIE_SHOWING_H__
#define __MOVIE_SHOWING_H__

#include <chrono>
#include <string>

#include "server_Movie.h"
#include "server_Room.h"

class Showing {
private:
	int id;
	Room *room;
	Movie movie;
	std::chrono::system_clock::time_point date;

	std::chrono::system_clock::time_point
	parseDatetime(std::string date, std::string time);

	std::string printDatetime() const;

public:
	Showing(int id, Room *room, Movie movie,
			std::chrono::system_clock::time_point date);

	Showing(int id, Room *room, Movie movie, std::string date,
			std::string time);

	Showing(const Showing &other);

	Showing(Showing &&other) noexcept;

	~Showing() = default;

	// Override less operator in order to work with std::set
	const bool operator<(const Showing &r) const;

	// Overloading equals operator
	bool operator==(const Showing &other) const;

	// Overloading the assignment by copy
	Showing &operator=(const Showing &other);

	// Overloading the assignment by movement
	Showing &operator=(Showing &&other) noexcept;

	// Overloading the std::string casting to obtain the showing information
	explicit operator std::string() const;

	bool hasDay(std::tm day) const;

	bool hasId(std::string id) const;

	std::string getSeats() const;

	void book(char row, int column, std::ostringstream &stream);

	// Overloading the << operator but we make it friend to be
	// callable from outside
	friend std::ostream &operator<<(std::ostream &out, const Showing &s);
};


#endif //__MOVIE_SHOWING_H__
