#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <unordered_set>
#include <set>

#include "server_Room.h"
#include "server_Movie.h"
#include "server_Showing.h"

class Server {
private:
	std::string port;
	std::set<Room*> rooms;
	std::set<Movie> movies;
	std::set<Showing> showings;

	Room* getRoomWithId(std::string id);

	Movie getMovieWithTitle(std::string title);

	std::set<Room*> parseRoomsCsv(std::string roomsCsvFilePath);

	std::set<Movie> parseMoviesCsv(std::string moviesCsvFilePath);

	std::set<Showing>
	parseShowingsCsv(std::string showingsCsvFilePath);

public:
	Server(std::string port, std::set<Room*> rooms,
		   std::set<Movie> movies, std::string showings_csv_file_path);

	Server(std::string port, std::string rooms_csv_file_path,
		   std::string movies_csv_file_path, std::string showings_csv_file_path);

	~Server();

	void listMoviesByLanguage(std::string language) const;

	void listMoviesByAge(std::string age_restriction) const;

	void listMoviesByGenre(std::string genre) const;

	void listShowingsForDay(std::tm day) const;

	void listSeatsFromShowingId(std::string id) const;

	void bookShowing(std::string showing_id, char row, int column);
};


#endif //__SERVER_H__