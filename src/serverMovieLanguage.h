#ifndef __MOVIE_LANGUAGE_H__
#define __MOVIE_LANGUAGE_H__

#include <string>

class MovieLanguage {
private:
	std::string movie_language;

	void validateLanguage();
public:
	explicit MovieLanguage(std::string genre);

	// Overloading equals operator
	bool operator==(const MovieLanguage &other) const;

	MovieLanguage(const MovieLanguage &other);

	MovieLanguage(MovieLanguage&& other) noexcept;

	MovieLanguage& operator=(const MovieLanguage &other);

	MovieLanguage& operator=(MovieLanguage&& other) noexcept;
};


#endif //__MOVIE_LANGUAGE_H__
