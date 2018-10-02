#ifndef __MOVIE_AGE_RESTRICTION_H__
#define __MOVIE_AGE_RESTRICTION_H__

#include <string>

class MovieAgeRestriction {
private:
	std::string age_restriction;

	void validateAgeRestriction();
public:
	explicit MovieAgeRestriction(std::string age_restriction);

	// Overloading equals operator
	bool operator==(const MovieAgeRestriction &other) const;

	MovieAgeRestriction(const MovieAgeRestriction &other);

	MovieAgeRestriction(MovieAgeRestriction&& other) noexcept;

	MovieAgeRestriction& operator=(const MovieAgeRestriction &other);

	MovieAgeRestriction& operator=(MovieAgeRestriction&& other) noexcept;
};


#endif //__MOVIE_AGE_RESTRICTION_H__
