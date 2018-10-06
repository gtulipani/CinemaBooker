#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

#include "server_CinemaMonitor.h"
#include "server_InvalidInputParamsException.h"
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

CinemaMonitor::CinemaMonitor(std::vector<Movie> &movies,
							 std::vector<Room *> &rooms,
							 std::vector<Showing> &showings) :
		movies(movies),
		rooms(rooms),
		showings(showings) {}

CinemaMonitor::CinemaMonitor(CinemaMonitor &&other) noexcept : CinemaMonitor(
		other.movies,
		other.rooms,
		other.showings) {}

void
CinemaMonitor::listMoviesByLanguage(const std::string &language,
									std::ostringstream &stream) {
	std::lock_guard<std::mutex> l(this->m);
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
CinemaMonitor::listMoviesByAge(const std::string &age_restriction,
							   std::ostringstream &stream) {
	std::lock_guard<std::mutex> l(this->m);
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

void CinemaMonitor::listMoviesByGenre(const std::string &genre,
									  std::ostringstream &stream) {
	std::lock_guard<std::mutex> l(this->m);
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

void CinemaMonitor::listSeatsFromShowingId(const std::string &id,
										   std::ostringstream &stream) {
	std::lock_guard<std::mutex> l(this->m);
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

void
CinemaMonitor::listShowingsForDay(const std::tm &day,
								  std::ostringstream &stream) {
	std::lock_guard<std::mutex> l(this->m);
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

void
CinemaMonitor::bookShowing(const std::string &showing_id,
						   const std::string &row,
						   int column,
						   std::ostringstream &stream) {
	std::lock_guard<std::mutex> l(this->m);
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

CinemaMonitor &CinemaMonitor::operator=(CinemaMonitor &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->movies = other.movies;
	this->rooms = other.rooms;
	this->showings = other.showings;

	return *this;
}

