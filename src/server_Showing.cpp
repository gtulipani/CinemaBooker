#include <utility>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "server_Showing.h"

#define DATE_TIME_OUTPUT_FORMAT "(DD/MM/AAAA) - (hh:mm)"

std::chrono::system_clock::time_point
Showing::parseDatetime(std::string date, std::string time) {
	std::tm tm = {};
	std::stringstream ss(date + " " + time);
	ss >> std::get_time(&tm, "%d/%m/%Y %H:%M");
	return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string Showing::printDatetime() const {
	time_t tt = std::chrono::system_clock::to_time_t(date);
	tm local_time = *localtime(&tt);
	char buffer[sizeof(DATE_TIME_OUTPUT_FORMAT)];
	std::strftime(buffer, sizeof(buffer), "(%d/%m/%Y) - (%H:%M)", &local_time);
	return std::string(buffer);
}

Showing::Showing(int id, Room* room, Movie movie,
						   std::chrono::system_clock::time_point date) :
		id(id),
		room(room),
		movie(std::move(movie)),
		date(date) {}

Showing::Showing(int id, Room* room, Movie movie, std::string date,
						   std::string time) : Showing(
		id,
		room,
		std::move(movie),
		parseDatetime(
				std::move(date),
				std::move(time))) {}

Showing::Showing(const Showing &other) :
		Showing(other.id, other.room, other.movie, other.date) {}

Showing::Showing(Showing &&other) noexcept : Showing(
		other.id,
		other.room,
		std::move(other.movie),
		other.date) {
	other.id = 0;
	other.room = nullptr;
}

const bool Showing::operator<(const Showing &r) const {
	return (this->id < r.id);
}

bool Showing::operator==(const Showing &other) const {
	return ((room == other.room) && (movie == other.movie) &&
			(date == other.date));
}

Showing &Showing::operator=(const Showing &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Free current Room
	delete[] this->room;

	this->id = other.id;
	this->room = other.room;
	this->movie = other.movie;
	this->date = other.date;

	return *this;
}

Showing &Showing::operator=(Showing &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	// Free current Room
	delete[] this->room;

	this->id = other.id;
	this->room = other.room;
	this->movie = std::move(other.movie);
	this->date = other.date;

	other.id = 0;
	other.room = nullptr;

	return *this;
}

Showing::operator std::string() const {
	std::ostringstream ss;
	ss << id << ": <Funcion para \"" << (std::string) movie << "\" en la sala "
	   << (std::string) *room << " con fecha " << printDatetime() << ">";
	return ss.str();
}

bool Showing::hasDay(std::tm day) const {
	time_t tt = std::chrono::system_clock::to_time_t(date);
	tm local_time = *localtime(&tt);
	return (local_time.tm_mday == day.tm_mday);
}

bool Showing::hasId(std::string id) const {
	return (std::to_string(this->id) == id);
}

std::string Showing::getSeats() const {
	return room->getSeats();
}

void Showing::book(char row, int column) {
	room->book(row, column);
}
