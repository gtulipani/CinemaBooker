#ifndef __MOVIE_GENRE_H__
#define __MOVIE_GENRE_H__

#include <string>

class MovieGenre {
private:
	std::string genre;

	void validateGenre();
public:
	explicit MovieGenre(std::string genre);

	// Overloading equals operator
	bool operator==(const MovieGenre &other) const;

	MovieGenre(const MovieGenre &other);

	MovieGenre(MovieGenre&& other) noexcept;

	MovieGenre& operator=(const MovieGenre &other);

	MovieGenre& operator=(MovieGenre&& other) noexcept;
};


#endif //C__MOVIE_GENRE_H__
