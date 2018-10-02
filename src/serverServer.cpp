#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "serverServer.h"
#include "serverCSVIterator.h"
#include "serverFileUnreadableException.h"
#include "serverRoomNotFoundException.h"
#include "serverMovieNotFoundException.h"
#include "serverMovieShowingNotFoundException.h"

/**
 * Define the friend function for the Movie
 */
std::ostream &operator<<(std::ostream &out, const Movie &movie) {
	out << (std::string) movie;
	return out;
}

/**
 * Define the friend function for the MovieShowing
 */
std::ostream &operator<<(std::ostream &out, const MovieShowing &movie_showing) {
	out << (std::string) movie_showing;
	return out;
}

Room Server::getRoomWithId(std::string id) {
	std::set<Room>::iterator it = std::find_if(
			rooms.begin(), rooms.end(), [id](const Room &room) {
				return room.hasId(id);
			});
	if (it != rooms.end()) {
		return *it;
	} else {
		throw RoomNotFoundException("Room with id " + id);
	}
	//return Room("1", "2D", "chica");
}

Movie Server::getMovieWithTitle(std::string title) {
	auto it = std::find_if
			(movies.begin(), movies.end(), [title](const Movie &movie) {
				return movie.hasTitle(title);
			});
	if (it != movies.end()) {
		return *it;
	} else {
		throw MovieNotFoundException("Movie with title " + title);
	}
}

std::set<Room> Server::parseRoomsCsv(std::string roomsCsvFilePath) {
	std::set<Room> rooms;
	std::fstream input_stream;
	input_stream.open(roomsCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw FileUnreadableException();
	}
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		rooms.insert(Room((*iterator)[0], (*iterator)[1], (*iterator)[2]));
	}

	return rooms;
}

std::set<Movie>
Server::parseMoviesCsv(std::string moviesCsvFilePath) {
	std::set<Movie> movies;
	std::fstream input_stream;
	input_stream.open(moviesCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw FileUnreadableException();
	}
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		movies.insert(Movie((*iterator)[0], (*iterator)[1], (*iterator)[2],
							(*iterator)[3]));
	}
	return movies;
}

std::set<MovieShowing>
Server::parseShowingsCsv(std::string showingsCsvFilePath) {
	std::set<MovieShowing> movie_showings;
	std::fstream input_stream;
	input_stream.open(showingsCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw FileUnreadableException();
	}
	int showing_id = 1;
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		movie_showings.insert(MovieShowing(
				showing_id++,
				getRoomWithId((*iterator)[0]),
				getMovieWithTitle((*iterator)[1]),
				(*iterator)[2],
				(*iterator)[3]));
	}
	/*MovieShowing showing(
			1,
			Room("1", "2D", "chica"),
			//getRoomWithId("A"),
			getMovieWithTitle("Megalodon (Castellano)"),
			"13/10/2018",
			"12:00");
	movie_showings.insert(showing);*/
	return movie_showings;
}

Server::Server(std::string port, std::set<Room> rooms,
			   std::set<Movie> movies,
			   std::string showings_csv_file_path) :
		port(std::move(port)),
		rooms(std::move(rooms)),
		movies(std::move(movies)) {
	showings = parseShowingsCsv(std::move(showings_csv_file_path));
}

Server::Server(std::string port, std::string rooms_csv_file_path,
			   std::string movies_csv_file_path,
			   std::string showings_csv_file_path) :
		Server(std::move(port),
			   parseRoomsCsv(std::move(rooms_csv_file_path)),
			   parseMoviesCsv(std::move(movies_csv_file_path)),
			   std::move(showings_csv_file_path)) {}

void Server::listMoviesByLanguage(MovieLanguage language) const {
	std::set<Movie> filtered_set;
	std::copy_if(
			movies.begin(),
			movies.end(),
			std::inserter(filtered_set, filtered_set.end()),
			[language](const Movie &m) {
				return m.hasLanguage(language);
			});
	std::for_each(filtered_set.begin(), filtered_set.end(), [](const Movie &m) {
		std::cout << m << std::endl;
	});
}

void Server::listMoviesByAge(MovieAgeRestriction age_restriction) const {
	std::set<Movie> filtered_set;
	std::copy_if(
			movies.begin(),
			movies.end(),
			std::inserter(filtered_set, filtered_set.end()),
			[age_restriction](const Movie &m) {
				return m.hasAgeRestriction(age_restriction);
			});
	std::for_each(filtered_set.begin(), filtered_set.end(), [](const Movie &m) {
		std::cout << m << std::endl;
	});
}

void Server::listMoviesByGenre(MovieGenre genre) const {
	std::set<Movie> filtered_set;
	std::copy_if(
			movies.begin(),
			movies.end(),
			std::inserter(filtered_set, filtered_set.end()),
			[genre](const Movie &m) {
				return m.hasGenre(genre);
			});
	std::for_each(filtered_set.begin(), filtered_set.end(), [](const Movie &m) {
		std::cout << m << std::endl;
	});
}

void Server::listShowingsForDay(std::tm day) const {
	std::set<MovieShowing> filtered_set;
	std::copy_if(
			showings.begin(),
			showings.end(),
			std::inserter(filtered_set, filtered_set.end()),
			[day](const MovieShowing &s) {
				return s.hasDay(day);
			});
	std::for_each(filtered_set.begin(), filtered_set.end(),
				  [](const MovieShowing &s) {
					  std::cout << s << std::endl;
				  });
}

void Server::listSeatsFromShowingId(std::string id) const {
	std::set<MovieShowing> filtered_set;
	std::copy_if(
			showings.begin(),
			showings.end(),
			std::inserter(filtered_set, filtered_set.end()),
			[id](const MovieShowing &s) {
				return s.hasId(id);
			});
	std::for_each(filtered_set.begin(), filtered_set.end(),
				  [](const MovieShowing &s) {
					  std::cout << s << std::endl;
					  std::cout << s.getSeats() << std::endl;
				  });
}

void Server::bookShowing(std::string showing_id, char row, int column) {
	bool showing_found = false;
	std::for_each(showings.begin(), showings.end(),
			[&](MovieShowing movie_showing) {
				if (movie_showing.hasId(showing_id)) {
					showing_found = true;
					movie_showing.book(row, column);
				}
			});
	if (!showing_found) {
		throw MovieShowingNotFoundException("MovieShowing with id " + showing_id);
	}
}
