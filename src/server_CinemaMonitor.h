#ifndef __SERVER_CINEMA_MONITOR_H__
#define __SERVER_CINEMA_MONITOR_H__

#include <vector>
#include <mutex>

#include "server_Room.h"
#include "server_Movie.h"
#include "server_Showing.h"

class CinemaMonitor {
private:
	std::mutex m;
	std::vector<Movie> &movies;
	std::vector<Room *> &rooms;
	std::vector<Showing> &showings;
public:
	CinemaMonitor(std::vector<Movie> &movies, std::vector<Room *> &rooms,
				  std::vector<Showing> &showings);

	// Disabling the constructor by copy because it contains references that may be modified
	CinemaMonitor(const CinemaMonitor &other) = delete;

	CinemaMonitor(CinemaMonitor &&other) noexcept;

	void
	listMoviesByLanguage(const std::string &language,
						 std::ostringstream &stream);

	void
	listMoviesByAge(const std::string &age_restriction,
					std::ostringstream &stream);

	void listMoviesByGenre(const std::string &genre,
						   std::ostringstream &stream);

	void listSeatsFromShowingId(const std::string &id,
								std::ostringstream &stream);

	void
	listShowingsForDay(const std::tm &day, std::ostringstream &stream);

	void
	bookShowing(const std::string &showing_id, const std::string &row, int column,
				std::ostringstream &stream);

	// Disabling the assignment by copy because it contains references that may be modified
	CinemaMonitor &operator=(const CinemaMonitor &other) = delete;

	// Overloading the assignment by movement
	CinemaMonitor &operator=(CinemaMonitor &&other) noexcept;
};


#endif //__SERVER_CINEMA_MONITOR_H__
