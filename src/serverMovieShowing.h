#ifndef __MOVIE_SHOWING_H__
#define __MOVIE_SHOWING_H__

#include <chrono>

#include "serverMovie.h"
#include "serverRoom.h"

class MovieShowing {
private:
	int id;
	Room room;
	Movie movie;
	std::chrono::system_clock::time_point date;

	std::chrono::system_clock::time_point
	parseDatetime(std::string date, std::string time);
	std::string printDatetime() const;

public:
	MovieShowing(int id, Room room, Movie movie,
				 std::chrono::system_clock::time_point date);

	MovieShowing(int id, Room room, Movie movie, std::string date, std::string time);

	MovieShowing(const MovieShowing &other);

	MovieShowing(MovieShowing&& other) noexcept;

	~MovieShowing() = default;

	// Override less operator in order to work with std::set
	const bool operator<(const MovieShowing &r) const;

	// Overloading equals operator
	bool operator==(const MovieShowing &other) const;

	// Overloading the assignment by copy
	MovieShowing& operator=(const MovieShowing &other);

	// Overloading the assignment by movement
	MovieShowing& operator=(MovieShowing&& other) noexcept;

	// Overloading the std::string casting to obtain the showing information
	explicit operator std::string() const;

	bool hasDay(std::tm day) const;

	bool hasId(std::string id) const;

	std::string getSeats() const;

	void book(char row, int column);

	// Overloading the << operator but we make it friend to be
	// callable from outside
	friend std::ostream &operator<<(std::ostream &out, const MovieShowing &s);
};


#endif //__MOVIE_SHOWING_H__
