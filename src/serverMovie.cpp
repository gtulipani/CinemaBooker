#include <utility>

#include "serverMovie.h"

Movie::Movie(std::string title, MovieLanguage language,
			 MovieAgeRestriction age_restriction, MovieGenre genre) :
		title(std::move(title)),
		language(std::move(language)),
		age_restriction(std::move(age_restriction)),
		genre(std::move(genre)) {}

Movie::Movie(std::string title, std::string language,
			 std::string age_restriction,
			 std::string genre) : Movie(
		std::move(title),
		MovieLanguage(std::move(language)),
		MovieAgeRestriction(std::move(age_restriction)),
		MovieGenre(std::move(genre))) {}

Movie::Movie(const Movie &other) : Movie(other.title, other.language,
										 other.age_restriction, other.genre) {}

Movie::Movie(Movie &&other) noexcept : Movie(std::move(other.title),
											 std::move(other.language),
											 std::move(other.age_restriction),
											 std::move(other.genre)) {}

size_t const Movie::hash() const {
	std::hash<std::string> hasher;
	return hasher(title);
}

const bool Movie::operator<(const Movie &r) const {
	return true;
}

bool Movie::operator==(const Movie &other) const {
	return ((title == other.title) && (language == other.language) &&
			(age_restriction == other.age_restriction) &&
			(genre == other.genre));
}

Movie &Movie::operator=(const Movie &other) {
	if (this == &other) {
		return *this; // other is myself!
	}
	this->title = other.title;
	this->language = other.language;
	this->age_restriction = other.age_restriction;
	this->genre = other.genre;

	return *this;
}

Movie &Movie::operator=(Movie &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->title = std::move(other.title);
	this->language = std::move(other.language);
	this->age_restriction = std::move(other.age_restriction);
	this->genre = std::move(other.genre);

	return *this;
}

Movie::operator std::string() const {
	return title;
}

bool Movie::hasTitle(std::string title) const {
	return (this->title == title);
}

bool Movie::hasLanguage(MovieLanguage language) const {
	return (this->language == language);
}

bool Movie::hasAgeRestriction(MovieAgeRestriction age_restriction) const {
	return (this->age_restriction == age_restriction);
}

bool Movie::hasGenre(MovieGenre genre) const {
	return (this->genre == genre);
}
