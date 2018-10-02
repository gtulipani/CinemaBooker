#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <unordered_set>
#include <set>

#include "serverRoom.h"
#include "serverMovie.h"
#include "serverMovieShowing.h"

class Server {
private:
	std::string port;
	std::set<Room> rooms;
	std::set<Movie> movies;
	std::set<MovieShowing> showings;

	Room getRoomWithId(std::string id);

	Movie getMovieWithTitle(std::string title);

	std::set<Room> parseRoomsCsv(std::string roomsCsvFilePath);

	std::set<Movie> parseMoviesCsv(std::string moviesCsvFilePath);

	std::set<MovieShowing>
	parseShowingsCsv(std::string showingsCsvFilePath);

public:
	Server(std::string port, std::set<Room> rooms,
		   std::set<Movie> movies, std::string showings_csv_file_path);

	Server(std::string port, std::string rooms_csv_file_path,
		   std::string movies_csv_file_path, std::string showings_csv_file_path);

	void listMoviesByLanguage(MovieLanguage language) const;

	void listMoviesByAge(MovieAgeRestriction age_restriction) const;

	void listMoviesByGenre(MovieGenre genre) const;

	void listShowingsForDay(std::tm day) const;

	void listSeatsFromShowingId(std::string id) const;

	void bookShowing(std::string showing_id, char row, int column);
};


#endif //__SERVER_H__
