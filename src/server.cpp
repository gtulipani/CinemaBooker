#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

#include "server_CSVIterator.h"
#include "server.h"
#include "server_RoomCreator.h"
#include "server_InputFileException.h"
#include "server_InvalidInputParamsException.h"
#include "server_ClientOperationException.h"
#include "server_ShowingsInputFileException.h"
#include "server_CinemaMonitor.h"
#include "server_AccepterThread.h"
#include "commons_Socket.h"

#define INVALID_GENRE_MESSAGE "Genero no reconocido"

#define SERVER_END_CHARACTER 'q'

void Server::deleteRooms(std::vector<Room *> rooms) {
	std::for_each(rooms.begin(), rooms.end(), [](Room *room) {
		delete room;
	});
}

Room *Server::getRoomWithId(std::string id) {
	auto it = std::find_if(
			rooms.begin(), rooms.end(), [id](Room *room) {
				return room->hasId(id);
			});
	if (it != rooms.end()) {
		return *it;
	} else {
		throw InvalidInputParamsException(
				"La sala " + id + " no existe en el sistema.");
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
		throw InvalidInputParamsException(
				"La película " + title + " no existe en el sistema.");
	}
}

std::vector<Room *> Server::parseRoomsCsv(std::string roomsCsvFilePath) {
	std::vector<Room *> rooms;
	std::fstream input_stream;
	input_stream.open(roomsCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw InputFileException(roomsCsvFilePath);
	}
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		rooms.emplace_back(
				RoomCreator::factoryMethod((*iterator)[0], (*iterator)[1],
										   (*iterator)[2]));
	}

	return rooms;
}

std::vector<Movie>
Server::parseMoviesCsv(std::string moviesCsvFilePath) {
	std::vector<Movie> movies;
	std::fstream input_stream;
	input_stream.open(moviesCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw InputFileException(moviesCsvFilePath);
	}
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		movies.emplace_back(
				Movie((*iterator)[0], (*iterator)[1], (*iterator)[2],
					  (*iterator)[3]));
	}
	return movies;
}

std::vector<Showing>
Server::parseShowingsCsv(std::string showingsCsvFilePath) {
	std::vector<Showing> movie_showings;
	std::fstream input_stream;
	input_stream.open(showingsCsvFilePath, std::ios::in);
	if (input_stream.fail()) {
		throw ShowingsInputFileException(showingsCsvFilePath);
	}
	int showing_id = 1;
	for (CSVIterator iterator(input_stream);
		 iterator != CSVIterator(); ++iterator) {
		movie_showings.emplace_back(Showing(
				showing_id++,
				getRoomWithId((*iterator)[0]),
				getMovieWithTitle((*iterator)[1]),
				(*iterator)[2],
				(*iterator)[3]));
	}
	return movie_showings;
}

Server::Server(std::string port, std::vector<Movie> movies,
			   std::vector<Room *> rooms,
			   std::string showings_csv_file_path) :
		port(std::move(port)),
		movies(std::move(movies)),
		rooms(std::move(rooms)) {
	try {
		showings = parseShowingsCsv(std::move(showings_csv_file_path));
	} catch (ShowingsInputFileException &e) {
		Server::deleteRooms(this->rooms);
		throw e;
	}
}

Server::Server(std::string port, std::string rooms_csv_file_path,
			   std::string movies_csv_file_path,
			   std::string showings_csv_file_path) :
		Server(std::move(port),
			   parseMoviesCsv(std::move(movies_csv_file_path)),
			   parseRoomsCsv(std::move(rooms_csv_file_path)),
			   std::move(showings_csv_file_path)) {}

Server::~Server() {
	deleteRooms(rooms);
}

void Server::start() {
	Socket socket{};
	socket.bind(port);

	CinemaMonitor monitor(movies, rooms, showings);

	AccepterThread accepter(socket, monitor);

	accepter.start();

	while (std::cin.peek() != SERVER_END_CHARACTER) {
	}

	// Stop accepting new connections
	socket.close();
	accepter.join();
}
