#include <utility>
#include <string>
#include <list>
#include <algorithm>

#include "server_Movie.h"
#include "server_InvalidInputParamsException.h"

#define INVALID_LANGUAGE_MESSAGE "Idioma no reconocido"
#define INVALID_AGE_MESSAGE "Edad no reconocida"
#define INVALID_GENRE_MESSAGE "Genero no reconocido"

std::string Movie::validateLanguage(std::string language) const {
	std::list<std::string> valid_languages{"ESP", "SUB"};
	if ((std::find(valid_languages.begin(), valid_languages.end(),
				   language)) == valid_languages.end()) {
		throw InvalidInputParamsException(INVALID_LANGUAGE_MESSAGE);
	} else {
		return language;
	}
}

std::string Movie::validateAgeRestriction(std::string age_restriction) const {
	std::list<std::string> valid_age_restrictions{"ATP", "+13", "+18"};
	if ((std::find(valid_age_restrictions.begin(), valid_age_restrictions.end(),
				   age_restriction)) == valid_age_restrictions.end()) {
		throw InvalidInputParamsException(INVALID_AGE_MESSAGE);
	} else {
		return age_restriction;
	}
}

std::string Movie::validateGenre(std::string genre) const {
	std::list<std::string> valid_genres{"Drama", "Accion", "Comedia",
										"Animacion", "Terror", "Suspenso"};
	if ((std::find(valid_genres.begin(), valid_genres.end(),
				   genre)) == valid_genres.end()) {
		throw InvalidInputParamsException(INVALID_GENRE_MESSAGE);
	} else {
		return genre;
	}
}

Movie::Movie(std::string title, std::string language,
			 std::string age_restriction,
			 std::string genre) :
		title(std::move(title)),
		language(validateLanguage(std::move(language))),
		age_restriction(validateAgeRestriction(std::move(age_restriction))),
		genre(validateGenre(std::move(genre))) {}

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

bool Movie::hasLanguage(std::string language) const {
	validateLanguage(language);
	return (this->language == language);
}

bool Movie::hasAgeRestriction(std::string age_restriction) const {
	validateAgeRestriction(age_restriction);
	return (this->age_restriction == age_restriction);
}

bool Movie::hasGenre(std::string genre) const {
	validateGenre(genre);
	return (this->genre == genre);
}
