#include "serverMovieLanguage.h"
#include "serverInvalidMovieException.h"

#include <list>

void MovieLanguage::validateLanguage() {
	std::list<std::string> valid_languages{"ESP", "SUB"};
	if ((std::find(valid_languages.begin(), valid_languages.end(),
				   movie_language)) ==
		valid_languages.end()) {
		throw InvalidMovieException("Invalid Language");
	}
}

MovieLanguage::MovieLanguage(std::string language) : movie_language(
		std::move(language)) {
	validateLanguage();
}

bool MovieLanguage::operator==(const MovieLanguage &other) const {
	return (movie_language == other.movie_language);
}

MovieLanguage::MovieLanguage(const MovieLanguage &other) : MovieLanguage(
		other.movie_language) {}

MovieLanguage::MovieLanguage(MovieLanguage &&other) noexcept : MovieLanguage(
		std::move(other.movie_language)) {}

MovieLanguage &MovieLanguage::operator=(const MovieLanguage &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->movie_language = other.movie_language;

	return *this;
}

MovieLanguage &MovieLanguage::operator=(MovieLanguage &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->movie_language = std::move(other.movie_language);

	return *this;
}
