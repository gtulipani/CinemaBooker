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
	std::vector<Room *> rooms;
	std::vector<Movie> movies;
	std::vector<Showing> showings;

	std::vector<std::string> split(const std::string &s, char delimiter);

	void processCommand(const std::string &input, Socket &client_socket);

	Room *getRoomWithId(std::string id);

	Movie getMovieWithTitle(std::string title);

	std::vector<Room *> parseRoomsCsv(std::string roomsCsvFilePath);

	std::vector<Movie> parseMoviesCsv(std::string moviesCsvFilePath);

	std::vector<Showing>
	parseShowingsCsv(std::string showingsCsvFilePath);

public:
	Server(std::string port, std::vector<Room *> rooms,
		   std::vector<Movie> movies, std::string showings_csv_file_path);

	Server(std::string port, std::string rooms_csv_file_path,
		   std::string movies_csv_file_path,
		   std::string showings_csv_file_path);

	~Server();

	void start();

	void
	listMoviesByLanguage(const std::string &language,
						 std::ostringstream &stream) const;

	void
	listMoviesByAge(const std::string &age_restriction,
					std::ostringstream &stream) const;

	void listMoviesByGenre(const std::string &genre,
						   std::ostringstream &stream) const;

	void listSeatsFromShowingId(const std::string &id,
								std::ostringstream &stream) const;

	void
	listShowingsForDay(const std::tm &day, std::ostringstream &stream) const;

	void
	bookShowing(const std::string &showing_id, const std::string &, int column,
				std::ostringstream &stream);
};


#endif //__SERVER_H__
