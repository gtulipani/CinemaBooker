#ifndef __MOVIE_SHOWING_NOT_FOUND_EXCEPTION_H__
#define __MOVIE_SHOWING_NOT_FOUND_EXCEPTION_H__

#include <stdexcept>
#include <string>

class MovieShowingNotFoundException : public std::runtime_error {
public:
	explicit MovieShowingNotFoundException(std::string message);
};


#endif //__MOVIE_SHOWING_NOT_FOUND_EXCEPTION_H__
