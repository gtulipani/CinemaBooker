#ifndef __MOVIE_NOT_FOUND_EXCEPTION_H__
#define __MOVIE_NOT_FOUND_EXCEPTION_H__

#include <stdexcept>
#include <string>

class MovieNotFoundException : public std::runtime_error {
public:
	explicit MovieNotFoundException(std::string message);
};


#endif //__MOVIE_NOT_FOUND_EXCEPTION_H__
