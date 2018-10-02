#include "serverMovieAgeRestriction.h"
#include "serverInvalidMovieException.h"

#include <list>

void MovieAgeRestriction::validateAgeRestriction() {
	std::list<std::string> valid_age_restrictions{"ATP", "+13", "+18"};
	if ((std::find(valid_age_restrictions.begin(), valid_age_restrictions.end(),
				   age_restriction)) ==
		valid_age_restrictions.end()) {
		throw InvalidMovieException("Invalid Age Restriction");
	}
}

MovieAgeRestriction::MovieAgeRestriction(std::string age_restriction)
		: age_restriction(std::move(age_restriction)) {
	validateAgeRestriction();
}

bool MovieAgeRestriction::operator==(const MovieAgeRestriction &other) const {
	return (age_restriction == other.age_restriction);
}

MovieAgeRestriction::MovieAgeRestriction(const MovieAgeRestriction &other) : MovieAgeRestriction(
		other.age_restriction) {}

MovieAgeRestriction::MovieAgeRestriction(MovieAgeRestriction &&other) noexcept : MovieAgeRestriction(
		std::move(other.age_restriction)) {}

MovieAgeRestriction &MovieAgeRestriction::operator=(const MovieAgeRestriction &other) {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->age_restriction = other.age_restriction;

	return *this;
}

MovieAgeRestriction &MovieAgeRestriction::operator=(MovieAgeRestriction &&other) noexcept {
	if (this == &other) {
		return *this; // other is myself!
	}

	this->age_restriction = std::move(other.age_restriction);

	return *this;
}
