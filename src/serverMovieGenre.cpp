#include <utility>

#include <list>
#include "serverMovieGenre.h"
#include "serverInvalidMovieException.h"

void MovieGenre::validateGenre() {
	std::list<std::string> valid_genres{"Drama", "Accion", "Comedia",
										"Animacion", "Terror", "Suspenso"};
	if ((std::find(valid_genres.begin(), valid_genres.end(), genre)) ==
		valid_genres.end()) {
		throw InvalidMovieException("Invalid Genre");
	}
}

MovieGenre::MovieGenre(std::string genre) : genre(std::move(genre)) {
	validateGenre();
}

bool MovieGenre::operator==(const MovieGenre &other) const {
	return (genre == other.genre);
}

MovieGenre::MovieGenre(const MovieGenre &other) : MovieGenre(
		other.genre) {}

MovieGenre::MovieGenre(MovieGenre &&other) noexcept : MovieGenre(
		std::move(other.genre)) {}

MovieGenre &MovieGenre::operator=(const MovieGenre &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->genre = other.genre;

	return *this;
}

MovieGenre &MovieGenre::operator=(MovieGenre &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->genre = std::move(other.genre);

	return *this;
}
