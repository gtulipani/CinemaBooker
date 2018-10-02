#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

#include "commons_CSVIterator.h"
#include "server.h"
#include "server_RoomCreator.h"
#include "server_InputFileException.h"
#include "server_ClientOperationException.h"

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
std::ostream &operator<<(std::ostream &out, const Showing &movie_showing) {
	out << (std::string) movie_showing;
	return out;
}

Room *Server::getRoomWithId(std::string id) {
	auto it = std::find_if(
			rooms.begin(), rooms.end(), [id](Room *room) {
				return room->hasId(id);
			});
	if (it != rooms.end()) {
		return *it;
	} else {
		throw ClientOperationException("Room with id " + id + " not found");
	}
}

Movie Server::getMovieWithTitle(std::string title) {
	auto it = std::find_if
			(movies.begin(), movies.end(), [title](const Movie &movie) {
				return movie.hasTitle(title);
			});
	if (it != movies.end()) {
		return *it;
	} else {
		throw ClientOperationException(
				"Movie with title " + title + " not found");
	}
}

std::set<Room *> Server::parseRoomsCsv(std::string roomsCsvFilePath) {
	std::set<Room *> rooms;
	std::fstream input_stream;
	input_stream.open(roomsCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw InputFileException();
	}
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		rooms.insert(RoomCreator::factoryMethod((*iterator)[0], (*iterator)[1],
												(*iterator)[2]));
	}

	return rooms;
}

std::set<Movie>
Server::parseMoviesCsv(std::string moviesCsvFilePath) {
	std::set<Movie> movies;
	std::fstream input_stream;
	input_stream.open(moviesCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw InputFileException();
	}
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		movies.insert(Movie((*iterator)[0], (*iterator)[1], (*iterator)[2],
							(*iterator)[3]));
	}
	return movies;
}

std::set<Showing>
Server::parseShowingsCsv(std::string showingsCsvFilePath) {
	std::set<Showing> movie_showings;
	std::fstream input_stream;
	input_stream.open(showingsCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw InputFileException();
	}
	int showing_id = 1;
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		movie_showings.insert(Showing(
				showing_id++,
				getRoomWithId((*iterator)[0]),
				getMovieWithTitle((*iterator)[1]),
				(*iterator)[2],
				(*iterator)[3]));
	}
	/*Showing showing(
			1,
			Room("1", "2D", "chica"),
			//getRoomWithId("A"),
			getMovieWithTitle("Megalodon (Castellano)"),
			"13/10/2018",
			"12:00");
	movie_showings.insert(showing);*/
	return movie_showings;
}

Server::Server(std::string port, std::set<Room *> rooms,
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

Server::~Server() {
	std::for_each(rooms.begin(), rooms.end(), [](Room *room) {
		std::cout << "Deleting room" << std::endl;
		delete room;
	});
}

void Server::listMoviesByLanguage(std::string language) const {
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

void Server::listMoviesByAge(std::string age_restriction) const {
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

void Server::listMoviesByGenre(std::string genre) const {
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
	std::set<Showing> filtered_set;
	std::copy_if(
			showings.begin(),
			showings.end(),
			std::inserter(filtered_set, filtered_set.end()),
			[day](const Showing &s) {
				return s.hasDay(day);
			});
	std::for_each(filtered_set.begin(), filtered_set.end(),
				  [](Showing s) {
					  std::cout << s << std::endl;
				  });
}

void Server::listSeatsFromShowingId(std::string id) const {
	std::set<Showing> filtered_set;
	std::copy_if(
			showings.begin(),
			showings.end(),
			std::inserter(filtered_set, filtered_set.end()),
			[id](const Showing &s) {
				return s.hasId(id);
			});
	std::for_each(filtered_set.begin(), filtered_set.end(),
				  [](const Showing &s) {
					  std::cout << s << std::endl;
					  std::cout << s.getSeats() << std::endl;
				  });
}

void Server::bookShowing(std::string showing_id, char row, int column) {
	bool showing_found = false;
	std::for_each(showings.begin(), showings.end(),
				  [&](Showing movie_showing) {
					  if (movie_showing.hasId(showing_id)) {
						  showing_found = true;
						  movie_showing.book(row, column);
					  }
				  });
	if (!showing_found) {
		throw ClientOperationException(
				"Showing with id " + showing_id + " not found");
	}
}
