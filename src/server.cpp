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
#include "commons_Socket.h"

#define LIST_BY_LANGUAGE_OPERATION_IDENTIFIER "IDIOMA"
#define LIST_BY_AGE_OPERATION_IDENTIFIER "EDAD"
#define LIST_BY_GENRE_OPERATION_IDENTIFIER "GENERO"
#define LIST_BY_DATE_OPERATION_IDENTIFIER "FECHA"
#define LIST_SEATS_OPERATION_IDENTIFIER "ASIENTOS"
#define BOOK_SEAT_OPERATION_IDENTIFIER "RESERVA"

#define INVALID_GENRE_MESSAGE "Genero no reconocido"

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

void Server::deleteRooms(std::vector<Room *> rooms) {
	std::for_each(rooms.begin(), rooms.end(), [](Room *room) {
		delete room;
	});
}

std::vector<std::string> Server::split(const std::string &s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream token_stream(s);
	while (std::getline(token_stream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void
Server::processCommand(const std::string &input, Socket &client_socket) {
	std::vector<std::string> words = split(input, ' ');
	std::ostringstream stream;
	if (words[0] == LIST_BY_LANGUAGE_OPERATION_IDENTIFIER) {
		listMoviesByLanguage(words[1], stream);
	} else if (words[0] == LIST_BY_AGE_OPERATION_IDENTIFIER) {
		listMoviesByAge(words[1], stream);
	} else if (words[0] == LIST_BY_GENRE_OPERATION_IDENTIFIER) {
		listMoviesByGenre(words[1], stream);
	} else if (words[0] == LIST_BY_DATE_OPERATION_IDENTIFIER) {
		std::tm tm{};
		std::istringstream ss(words[1]);
		ss >> std::get_time(&tm, "%d/%m/%Y");
		listShowingsForDay(tm, stream);
	} else if (words[0] == LIST_SEATS_OPERATION_IDENTIFIER) {
		listSeatsFromShowingId(words[1], stream);
	} else if (words[0] == BOOK_SEAT_OPERATION_IDENTIFIER) {
		bookShowing(words[1], words[2], std::stoi(words[3]), stream);
	} else {
		throw ClientOperationException("Operation invalid: " + input);
	}
	std::string out = stream.str();
	unsigned long message_size = out.size();
	client_socket.send_int((int) message_size);
	client_socket.send(out, message_size);
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

	Socket client_socket = socket.accept();

	// Receive commands from the socket
	std::string input;
	std::string output;
	long bytes_received = 0;
	do {
		int size_len = client_socket.receive_int();
		bytes_received = client_socket.receive(input,
											   static_cast<unsigned long>(size_len));
		if (bytes_received > 0) {
			processCommand(input, client_socket);
		}
	} while (bytes_received > 0);
}

void
Server::listMoviesByLanguage(const std::string &language,
							 std::ostringstream &stream) const {
	std::vector<Movie> filtered_vector;
	try {
		std::copy_if(
				movies.begin(),
				movies.end(),
				std::inserter(filtered_vector, filtered_vector.end()),
				[language](const Movie &m) {
					return m.hasLanguage(language);
				});
		std::for_each(filtered_vector.begin(), filtered_vector.end(),
					  [&stream](const Movie &m) {
						  stream << m << std::endl;
					  });
	} catch (InvalidInputParamsException &e) {
		stream << e.what() << std::endl;
	}

}

void
Server::listMoviesByAge(const std::string &age_restriction,
						std::ostringstream &stream) const {
	std::vector<Movie> filtered_vector;
	try {
		std::copy_if(
				movies.begin(),
				movies.end(),
				std::inserter(filtered_vector, filtered_vector.end()),
				[age_restriction](const Movie &m) {
					return m.hasAgeRestriction(age_restriction);
				});
		std::for_each(filtered_vector.begin(), filtered_vector.end(),
					  [&stream](const Movie &m) {
						  stream << m << std::endl;
					  });
	} catch (InvalidInputParamsException &e) {
		stream << e.what() << std::endl;
	}
}

void
Server::listMoviesByGenre(const std::string &genre,
						  std::ostringstream &stream) const {
	std::vector<Movie> filtered_vector;
	try {
		std::copy_if(
				movies.begin(),
				movies.end(),
				std::inserter(filtered_vector, filtered_vector.end()),
				[genre](const Movie &m) {
					return m.hasGenre(genre);
				});
		std::for_each(filtered_vector.begin(), filtered_vector.end(),
					  [&stream](const Movie &m) {
						  stream << m << std::endl;
					  });
	} catch (InvalidInputParamsException &e) {
		stream << e.what() << std::endl;
	}
}

void
Server::listSeatsFromShowingId(const std::string &id,
							   std::ostringstream &stream) const {
	std::vector<Showing> filtered_vector;
	std::copy_if(
			showings.begin(),
			showings.end(),
			std::inserter(filtered_vector, filtered_vector.end()),
			[id](const Showing &s) {
				return s.hasId(id);
			});
	std::for_each(filtered_vector.begin(), filtered_vector.end(),
				  [&stream](const Showing &s) {
					  stream << s << std::endl;
					  stream << s.getSeats() << std::endl;
				  });
}

void Server::listShowingsForDay(const std::tm &day,
								std::ostringstream &stream) const {
	std::vector<Showing> filtered_vector;
	std::copy_if(
			showings.begin(),
			showings.end(),
			std::inserter(filtered_vector, filtered_vector.end()),
			[day](const Showing &s) {
				return s.hasDay(day);
			});
	std::for_each(filtered_vector.begin(), filtered_vector.end(),
				  [&stream](Showing s) {
					  stream << s << std::endl;
				  });
}

void Server::bookShowing(const std::string &showing_id, const std::string &row,
						 int column,
						 std::ostringstream &stream) {
	char row_identifier = row[0];
	auto it = std::find_if(showings.begin(), showings.end(),
						   [&](Showing s) {
							   return s.hasId(showing_id);
						   });
	if (it != showings.end()) {
		it->book(row_identifier, column, stream);
	} else {
		throw ClientOperationException("Seat exceeds valid range");
	}
}
