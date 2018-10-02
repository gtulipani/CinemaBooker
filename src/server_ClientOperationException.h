#ifndef __MOVIE_NOT_FOUND_EXCEPTION_H__
#define __MOVIE_NOT_FOUND_EXCEPTION_H__

#include <stdexcept>
#include <string>

class ClientOperationException : public std::runtime_error {
public:
	explicit ClientOperationException(std::string message);
};


#endif //__MOVIE_NOT_FOUND_EXCEPTION_H__
