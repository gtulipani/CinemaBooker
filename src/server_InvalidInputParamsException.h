#ifndef __INVALID_MOVIE_GENRE_EXCEPTION_H__
#define __INVALID_MOVIE_GENRE_EXCEPTION_H__

#include <stdexcept>
#include <string>

class InvalidInputParamsException : public std::runtime_error {
public:
	explicit InvalidInputParamsException(std::string message);
};


#endif //__INVALID_MOVIE_GENRE_EXCEPTION_H__
