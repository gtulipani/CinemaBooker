#include <utility>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "serverMovieShowing.h"

#define DATE_TIME_OUTPUT_FORMAT "(DD/MM/AAAA) - (hh:mm)"

std::chrono::system_clock::time_point
MovieShowing::parseDatetime(std::string date, std::string time) {
	std::tm tm = {};
	std::stringstream ss(date + " " + time);
	ss >> std::get_time(&tm, "%d/%m/%Y %H:%M");
	return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string MovieShowing::printDatetime() const {
	time_t tt = std::chrono::system_clock::to_time_t(date);
	tm local_time = *localtime(&tt);
	char buffer[sizeof(DATE_TIME_OUTPUT_FORMAT)];
	std::strftime(buffer, sizeof(buffer), "(%d/%m/%Y) - (%H:%M)", &local_time);
	return std::string(buffer);
}

MovieShowing::MovieShowing(int id, Room room, Movie movie,
						   std::chrono::system_clock::time_point date) :
		id(id),
		room(std::move(room)),
		movie(std::move(movie)),
		date(date) {}

MovieShowing::MovieShowing(int id, Room room, Movie movie, std::string date,
						   std::string time) : MovieShowing(
		id,
		std::move(room),
		std::move(movie),
		parseDatetime(
				std::move(date),
				std::move(time))) {}

MovieShowing::MovieShowing(const MovieShowing &other) :
		MovieShowing(other.id, other.room, other.movie, other.date) {}

MovieShowing::MovieShowing(MovieShowing &&other) noexcept : MovieShowing(
		other.id,
		std::move(other.room),
		std::move(other.movie),
		other.date) {
	other.id = 0;
}

const bool MovieShowing::operator<(const MovieShowing &r) const {
	return (this->id < r.id);
}

bool MovieShowing::operator==(const MovieShowing &other) const {
	return ((room == other.room) && (movie == other.movie) &&
			(date == other.date));
}

MovieShowing &MovieShowing::operator=(const MovieShowing &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = other.id;
	this->room = other.room;
	this->movie = other.movie;
	this->date = other.date;

	return *this;
}

MovieShowing &MovieShowing::operator=(MovieShowing &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->id = other.id;
	this->room = std::move(other.room);
	this->movie = std::move(other.movie);
	this->date = other.date;

	other.id = 0;

	return *this;
}

MovieShowing::operator std::string() const {
	std::ostringstream ss;
	ss << id << ": <Funcion para \"" << (std::string) movie << "\" en la sala "
	   << (std::string) room << " con fecha " << printDatetime() << ">";
	return ss.str();
}

bool MovieShowing::hasDay(std::tm day) const {
	time_t tt = std::chrono::system_clock::to_time_t(date);
	tm local_time = *localtime(&tt);
	return (local_time.tm_mday == day.tm_mday);
}

bool MovieShowing::hasId(std::string id) const {
	return (std::to_string(this->id) == id);
}

std::string MovieShowing::getSeats() const {
	return room.getSeats();
}

void MovieShowing::book(char row, int column) {
	room.book(row, column);
}
