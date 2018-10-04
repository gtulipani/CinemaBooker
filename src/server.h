#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <unordered_set>
#include <set>
#include <vector>
#include <map>

#include "server_Room.h"
#include "server_Movie.h"
#include "server_Showing.h"
#include "commons_Socket.h"
#include "server_Operation.h"

class Server {
private:
	std::string port;
	std::set<Room *> rooms;
	std::set<Movie> movies;
	std::set<Showing> showings;

	void processCommand(const std::string &input, Socket &client_socket);

	Room *getRoomWithId(std::string id);

	Movie getMovieWithTitle(std::string title);

	std::set<Room *> parseRoomsCsv(std::string roomsCsvFilePath);

	std::set<Movie> parseMoviesCsv(std::string moviesCsvFilePath);

	std::set<Showing>
	parseShowingsCsv(std::string showingsCsvFilePath);

public:
	Server(std::string port, std::set<Room *> rooms,
		   std::set<Movie> movies, std::string showings_csv_file_path);

	Server(std::string port, std::string rooms_csv_file_path,
		   std::string movies_csv_file_path,
		   std::string showings_csv_file_path);

	~Server();

	void start();

	void listMoviesByLanguage(std::string language, std::string &out) const;

	void listMoviesByAge(std::string age_restriction, std::string &out) const;

	void listMoviesByGenre(std::string genre, std::string &out) const;

	void listSeatsFromShowingId(std::string id, std::string &out) const;

	void listShowingsForDay(std::tm day, std::string &out) const;

	void
	bookShowing(std::string showing_id, char row, int column, std::string &out);
};


#endif //__SERVER_H__
