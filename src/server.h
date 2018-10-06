#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <unordered_set>
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
	std::vector<Movie> movies;
	std::vector<Room *> rooms;
	std::vector<Showing> showings;

	static void deleteRooms(std::vector<Room *> rooms);

	Room *getRoomWithId(std::string id);

	Movie getMovieWithTitle(std::string title);

	std::vector<Room *> parseRoomsCsv(std::string roomsCsvFilePath);

	std::vector<Movie> parseMoviesCsv(std::string moviesCsvFilePath);

	std::vector<Showing>
	parseShowingsCsv(std::string showingsCsvFilePath);

public:
	Server(std::string port, std::vector<Movie> movies, std::vector<Room *> rooms, std::string showings_csv_file_path);

	Server(std::string port, std::string rooms_csv_file_path,
		   std::string movies_csv_file_path,
		   std::string showings_csv_file_path);

	~Server();

	void start();
};


#endif //__SERVER_H__
