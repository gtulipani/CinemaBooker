#ifndef __MOVIE_H__
#define __MOVIE_H__

#include <string>
#include "serverMovieLanguage.h"
#include "serverMovieAgeRestriction.h"
#include "serverMovieGenre.h"

class Movie {
private:
	std::string title;
	MovieLanguage language;
	MovieAgeRestriction age_restriction;
	MovieGenre genre;
public:
	Movie(std::string title, MovieLanguage language,
		  MovieAgeRestriction age_restriction, MovieGenre genre);

	Movie(std::string title, std::string language, std::string age_restriction,
		  std::string genre);

	Movie(const Movie &other);

	Movie(Movie&& other) noexcept;

	// Define hash function in order to work with std:unordered_set
	size_t const hash() const;

	// Override less operator in order to work with std::set
	const bool operator<(const Movie &r) const;

	// Overloading equals operator
	bool operator==(const Movie &other) const;

	// Overloading the assignment by copy
	Movie& operator=(const Movie &other);

	// Overloading the assignment by movement
	Movie& operator=(Movie&& other) noexcept;

	// Overloading the std::string casting to obtain the title
	explicit operator std::string() const;

	bool hasTitle(std::string title) const;

	bool hasLanguage(MovieLanguage language) const;

	bool hasAgeRestriction(MovieAgeRestriction age_restriction) const;

	bool hasGenre(MovieGenre genre) const;

	void foo() {

	}

	// Overloading the << operator but we make it friend to be
	// callable from outside
	friend std::ostream &operator<<(std::ostream &out, const Movie &m);
};


#endif //__MOVIE_H__
